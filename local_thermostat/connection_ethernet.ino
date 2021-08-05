/*
 * Settings Ethernet connection
 * MQTT via Ethernet
*/

#include <SPI.h>
#include "EthernetSPI2.h"
#include "EthernetUdp.h"
#include <PubSubClient.h>
#include <stdlib.h>

EthernetClient ethClient;
PubSubClient mqttClientEthernet(ethClient); 

// A UDP instance to let us send and receive packets over UDP.
EthernetUDP udp;



/*
 * Wiz W5500 reset function.  Change this for the specific reset
 * sequence required for your particular board or module.
 */
void wizReset() 
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
    
void setupEthernet() 
{
    delay(500);
    Serial.println("\n\tUDP NTP Client v3.0\r\n");

    // Use Ethernet.init(pin) to configure the CS pin.
    Ethernet.init(ETHERNET_PIN_SPI_CS);  
    wizReset();

    /* 
     * Network configuration - all except the MAC are optional.
     *
     * IMPORTANT NOTE - The mass-produced W5500 boards do -not-
     *                  have a built-in MAC address (depite 
     *                  comments to the contrary elsewhere). You
     *                  -must- supply a MAC address here.
     */
    Serial.println("Starting ETHERNET connection...");
    Ethernet.begin(MAC_ADDRESS, IP, DNS_SERVER, GATEWAY, SUBNET_MASK);
    // Enable DHCP
    //Ethernet.begin(eth_MAC);

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
        isConnection = false;
    } 
    else 
    {
        isConnection = true;
        Serial.println(" OK");
        udp.begin(localPort);
        setMqtt();
    }
}

void callbackMqttEthernet(char* topic, byte* payload, unsigned int length) 
{
  for (int i = 0; i < length; i++) 
  {    
    parseTopic(topic, (char*)payload);
  }
}

void setMqtt() 
{
  mqttClientEthernet.setServer(MQTT_HOST, MQTT_PORT);
  // Sets the callback function
  mqttClientEthernet.setCallback(callbackMqttEthernet);
  connectMqttEthernet();
}

void connectMqttEthernet() 
{
  if (!mqttClientEthernet.connected()) 
  {
    String clientId = roomName;
    //clientId += String(random(0xffff), HEX);     
    if (mqttClientEthernet.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) 
    {
      setSubscribe();
      Serial.println("Connected to MQTT broker.");
    }
    else
    {
      Serial.println("Problem with connection to MQTT broker.");
    }
  }
}

void mqttLoopEthernet()
{
  if(getStatusEthernet())
  {
    if (!mqttClientEthernet.connected())
    {
      setMqtt();
    }
    else
    {
       mqttClientEthernet.loop();
    }
  }
}

bool getStatusEthernet()
{
  for (uint8_t i = 0; i <= 20; i++) 
  {
    if ((Ethernet.hardwareStatus() == EthernetNoHardware) || (Ethernet.linkStatus() == LinkOFF)) 
    {
      isConnection = false;
      resetTimersFromReconnectionOfEthernet = true;
      delay(80);
      Serial.println("Disconnect cable");
    } 
    else 
    {
      isConnection = true;
      Serial.println("Connect cable");
      break;
    }
  }

  return isConnection;
}
