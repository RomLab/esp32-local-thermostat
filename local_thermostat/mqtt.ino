/*
 *   $Id: ESP32_NTP.ino,v 1.8 2019/04/04 04:48:23 gaijin Exp $
 *
 *  UDP NTP client example program.
 * 
 *  Get the time from a Network Time Protocol (NTP) time server
 *  Demonstrates use of UDP sendPacket and ReceivePacket
 * 
 *  Created:  04 Sep 2010 by Michael Margolis
 *  Modified: 09 Apr 2012 by Tom Igoe
 *  Modified: 02 Sep 2015 by Arturo Guadalupi
 *  Munged:   04 Apr 2019 by PuceBaboon (for the ESP32 with a W5500 module)
 * 
 */

#include <SPI.h>
#include "EthernetSPI2.h"
#include "EthernetUdp.h"

#include <PubSubClient.h>
#include <stdlib.h>

const int NTP_PACKET_SIZE = 48;   // NTP time stamp is in the first 48 bytes of the message.
byte packetBuffer[NTP_PACKET_SIZE]; // Buffer for both incoming and outgoing packets.

// A UDP instance to let us send and receive packets over UDP.
EthernetUDP Udp;

char data[100];

EthernetClient ethClient;
PubSubClient mqttClient(ethClient); 
char *mqttServer = "broker.hivemq.com";///"192.168.11.247";//"broker.hivemq.com";//"172.16.108.22";
int mqttPort = 1883;
//const char* mqttUser = "homeassistant";
//const char* mqttPassword = "VelmiSilneHesloProHomeassistant";

// Icons
extern uint8_t online[];
extern uint8_t offline[];
/*
 * Wiz W5500 reset function.  Change this for the specific reset
 * sequence required for your particular board or module.
 */
void WizReset() 
{
    Serial.print("Resetting Wiz W5500 Ethernet Board...  ");
    pinMode(ETHERNET_PIN_RST, OUTPUT);
    digitalWrite(ETHERNET_PIN_RST, HIGH);
    delay(250);
    digitalWrite(ETHERNET_PIN_RST, LOW);
    delay(50);
    digitalWrite(ETHERNET_PIN_RST, HIGH);
    delay(350);
    Serial.println("Done.");
}


/*
 * This is a crock. It's here in an effort
 * to help people debug hardware problems with
 * their W5100 ~ W5500 board setups.  It's 
 * a copy of the Ethernet library enums and
 * should, at the very least, be regenerated
 * from Ethernet.h automatically before the
 * compile starts (that's a TODO item).
 *
 */
/*
 * Print the result of the hardware status enum
 * as a string.
 * Ethernet.h currently contains these values:-
 *
 *  enum EthernetHardwareStatus {
 *    EthernetNoHardware,
 *    EthernetW5100,
 *    EthernetW5200,
 *    EthernetW5500
 *  };
 *
 */
void prt_hwval(uint8_t refval) 
{
    switch (refval) 
    {
      case 0:
         Serial.println("No hardware detected.");
          break;
     case 1:
          Serial.println("WizNet W5100 detected.");
         break;
      case 2:
          Serial.println("WizNet W5200 detected.");
          break;
      case 3:
          Serial.println("WizNet W5500 detected.");
          break;
      default:
          Serial.println
             ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

/*
 * Print the result of the ethernet connection
 * status enum as a string.
 * Ethernet.h currently contains these values:-
 *
 *  enum EthernetLinkStatus {
 *     Unknown,
 *     LinkON,
 *     LinkOFF
 *  };
 *
 */
void prt_ethval(uint8_t refval) {
    switch (refval) 
    {
    case 0:
        Serial.println("Uknown status.");
        break;
    case 1:
        Serial.println("Link flagged as UP.");
        break;
    case 2:
        Serial.println("Link flagged as DOWN. Check cable connection.");
        break;
    default:
        Serial.println
            ("UNKNOWN - Update espnow_gw.ino to match Ethernet.h");
    }
}

    
void mqttSetup() {

    delay(500);
    Serial.println("\n\tUDP NTP Client v3.0\r\n");

    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(ETHERNET_PIN_SPI_CS);  
    WizReset();

    /* 
     * Network configuration - all except the MAC are optional.
     *
     * IMPORTANT NOTE - The mass-produced W5500 boards do -not-
     *                  have a built-in MAC address (depite 
     *                  comments to the contrary elsewhere). You
     *                  -must- supply a MAC address here.
     */
    Serial.println("Starting ETHERNET connection...");
    Ethernet.begin(eth_MAC, eth_IP, eth_DNS, eth_GW, eth_MASK);
    Serial.println("test");
    // Enable DHCP
   // Ethernet.begin(eth_MAC);

    delay(200);

    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());

    /*
     * Sanity checks for W5500 and cable connection.
     */
    Serial.print("Checking connection.");
    if (!getStatusEthernet()) 
    {
        Serial.println("\n\r\tHardware fault, or cable problem... cannot continue.");
        Serial.print("Hardware Status: ");
        prt_hwval(Ethernet.hardwareStatus());
        Serial.print("   Cable Status: ");
        prt_ethval(Ethernet.linkStatus());
        isConnectedEthernet = false;
       /* while (true) 
        {
            delay(10);          // Halt.
        }*/
    } 
    else 
    {
        isConnectedEthernet = true;
        Serial.println(" OK");
        Udp.begin(localPort);
        SetupMqtt();
    }
}

bool getStatusEthernet()
{
   bool rdy_flag = false;
   for (uint8_t i = 0; i <= 20; i++) 
    {
        if ((Ethernet.hardwareStatus() == EthernetNoHardware)
            || (Ethernet.linkStatus() == LinkOFF)) {
            Serial.print(".");
            rdy_flag = false;
            delay(80);
        } 
        else 
        {
            rdy_flag = true;
            break;
        }
    }

    return rdy_flag;
}

void mqttLoop()
{
   if(isConnectedEthernet)
  {
    if (!mqttClient.connected())
    {
      tft.drawBitmap(0, 0, online, 20, 20, ILI9341_RED);
      Reconnect();
    }
    else
    {
      tft.drawBitmap(0, 0, online, 20, 20, ILI9341_GREEN);
      mqttClient.loop();
    }
  }
  else
  {
    tft.drawBitmap(0, 0, online, 20, 20, ILI9341_RED);
  }
}
void SendTemperature(float temperature) {

  if(isConnectedEthernet)
  {
    //if (!mqttClient.connected())
    //  Reconnect();
      
   // mqttClient.loop();
    
    // Publishing data throgh MQTT
    sprintf(data, "%f", temperature);
    //Serial.println(data);
    String s = "home/first-floor/"+roomName+"/temperature";
    int str_len = s.length() + 1; 
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
    mqttClient.publish(char_array, data);
  }
}

void SendRequiredTemperature(float requiredTemperature) 
{

    sprintf(data, "%f", requiredTemperature);
    String s = "home/first-floor/"+roomName+"/required-temperature-from-device";
    int str_len = s.length() + 1; 
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
    mqttClient.publish(char_array, data);
}

void Callback(char* topic, byte* payload, unsigned int length) 
{

  for (int i = 0; i < length; i++) 
  {
    String s = "home/first-floor/"+roomName+"/required-temperature-from-system";
    int str_len = s.length() + 1; 
    char char_array[str_len];
    s.toCharArray(char_array, str_len);
    if(strcmp(topic,char_array)==0)
    {
      //String s = String(((char)payload[i]));
      String s = String((char*)payload);
      float value = s.toFloat();
      
      float real =  value * 10;
      int rel_int = (int)real;
    
      requiredTemperature = (float)rel_int/10;
      writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5, 1);
    }
  }
}

void SetupMqtt() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(Callback);
}

void Reconnect() 
{
  if(getStatusEthernet())
  {
    while (!mqttClient.connected()) 
    {
      String clientId = roomName;
      //clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str()/*, mqttUser, mqttPassword*/)) 
      {
        // Subscribe
        String topicFromSystem = "home/first-floor/"+roomName+"/required-temperature-from-system";
        int lengthTopicFromSystem = topicFromSystem.length() + 1; 
        char topicFromSystemArray[lengthTopicFromSystem];
        topicFromSystem.toCharArray(topicFromSystemArray, lengthTopicFromSystem);
        mqttClient.subscribe(topicFromSystemArray, 1);
      }  
    }
  }
  else
  {
    Serial.println("Disconnect cable");
  }
}
