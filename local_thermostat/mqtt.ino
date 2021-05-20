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
//#include <Ethernet.h>
//#include <EthernetUdp.h>
#include "EthernetSPI2.h"
#include "EthernetUdp.h"
#include "local_config.h"  // <--- Change settings for YOUR network here.
#include <PubSubClient.h>
#include <stdlib.h>

const int NTP_PACKET_SIZE = 48;   // NTP time stamp is in the first 48 bytes of the message.
byte packetBuffer[NTP_PACKET_SIZE]; // Buffer for both incoming and outgoing packets.

// A UDP instance to let us send and receive packets over UDP.
EthernetUDP Udp;

char data[100];

EthernetClient ethClient;
PubSubClient mqttClient(ethClient); 
char *mqttServer = "broker.hivemq.com";//"172.16.108.22";
int mqttPort = 1883;
const char* mqttUser = "homeassistant";
const char* mqttPassword = "VelmiSilneHesloProHomeassistant";

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
    pinMode(RESET_P, OUTPUT);
    digitalWrite(RESET_P, HIGH);
    delay(250);
    digitalWrite(RESET_P, LOW);
    delay(50);
    digitalWrite(RESET_P, HIGH);
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


void MqttSetup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("\n\tUDP NTP Client v3.0\r\n");

    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(15);           // GPIO5 on the ESP32.
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
    // Enable DHCP
    //Ethernet.begin(eth_MAC);

    delay(200);

    Serial.print("Ethernet IP is: ");
    Serial.println(Ethernet.localIP());

    /*
     * Sanity checks for W5500 and cable connection.
     */
    Serial.print("Checking connection.");
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
    if (rdy_flag == false) 
    {
        Serial.println
            ("\n\r\tHardware fault, or cable problem... cannot continue.");
        Serial.print("Hardware Status: ");
        prt_hwval(Ethernet.hardwareStatus());
        Serial.print("   Cable Status: ");
        prt_ethval(Ethernet.linkStatus());
        while (true) 
        {
            delay(10);          // Halt.
        }
    } 
    else 
    {
        Serial.println(" OK");
    }

    Udp.begin(localPort);
    
    SetupMqtt();
}

void MqttLoop()
{
  if (!mqttClient.connected())
  {
    tft.drawBitmap(0, 0, online, 20, 20, ILI9341_RED);
    Reconnect();
  }
  else
  {
    tft.drawBitmap(0, 0, online, 20, 20, ILI9341_GREEN);
  }
          
   mqttClient.loop();
}
void SendTemperature(float temperature) {
  
    //if (!mqttClient.connected())
    //  Reconnect();
      
   // mqttClient.loop();
    
    // Publishing data throgh MQTT
    sprintf(data, "%f", temperature);
    Serial.println(data);
    mqttClient.publish("home/firstfloor/test_room/temperature", data);
}

void SendRequiredTemperature(float requiredTemperature) {
    // Publishing data throgh MQTT
        Serial.println("Pozadovana teplota");
    sprintf(data, "%f", requiredTemperature);
    mqttClient.publish("home/firstfloor/test_room/required_temperature", data);
}

void Callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  Serial.print(topic);
  for (int i = 0; i < length; i++) 
  {
    if(strcmp(topic,"home/firstfloor/test_room/local_thermostat/required_temperature")==0)
    {
      //String s = String(((char)payload[i]));
      String s = String((char*)payload);
      float value = s.toFloat();
      requireTemperature = value;
      WriteTemperature(value, 40, 135, ILI9341_GREEN, 5);
       Serial.print(String(value));
    }
   
  }
}

void SetupMqtt() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(Callback);
}

void Reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) 
  {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "client1";
      //clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str()/*, mqttUser, mqttPassword*/)) 
      {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("home/firstfloor/test_room/local_thermostat/required_temperature");
      }  
  }
}
