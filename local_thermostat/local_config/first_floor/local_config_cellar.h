/*
 *   $Id: local_config.h,v 1.5 2019/04/04 23:06:53 gaijin Exp $
 *
 * Change settings below to customize for -YOUR- local network.
 * 
 */


/*
 * W5500 "hardware" MAC address.
 */
uint8_t eth_MAC[] = { 0xDC, 0xA6, 0x32, 0x25, 0x1D, 0x16 };


/*
 * Define the static network settings for this gateway's ETHERNET connection
 * on your LAN.  These values must match YOUR SPECIFIC LAN.  The "eth_IP"
 * is the IP address for this gateway's ETHERNET port.
 */
IPAddress IP(192, 168, 11, 16);		// *** CHANGE THIS to something relevant for YOUR LAN. ***
IPAddress SUBNET__MASK(255, 255, 255, 0);		// Subnet mask.
IPAddress DNS_SERVER(8, 8, 8, 8);		// *** CHANGE THIS to match YOUR DNS server.           ***
IPAddress GATEWAY(192, 168, 11, 254);		// *** CHANGE THIS to match YOUR Gateway (router).     ***


// Type: ETHERNET, WIFI
enum connection {
  ETHERNET,
  WIFI,
};

connection typeOfConnection = ETHERNET;

// WIFI settings
#define WIFI_SSID "AZGARD"
#define WIFI_PASSWORD "darkflame"


// MQTT settings
#define MQTT_HOST IPAddress(192, 168, 11, 247)
//#define MQTT_HOST "broker.hivemq.com"
#define MQTT_PORT 1883

#define MQTT_USER "homeassistant"
#define MQTT_PASSWORD "VelmiSilneHesloProHomeassistant"

String roomName = "cellar";

String numberOfFloor = "first-floor";
//String numberOfFloor = "second-floor";


// W5500
#define RESET_P 27        // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.

const uint16_t localPort = 55432;   // Local port for UDP packets.

/*
 * Choose the NTP server pool for your geographical region for best
 * performance (fewer lost packets).
 *
 * *** Uncomment only one of the following "timeServer[]" defines. ***
 */
const char timeServer[] = "pool.ntp.org";   // Default NTP server pool.
// const char timeServer[] = "africa.pool.ntp.org";   // Regional server pool.
// const char timeServer[] = "asia.pool.ntp.org";   // Regional server pool.
// const char timeServer[] = "europe.pool.ntp.org";   // Regional server pool.
// const char timeServer[] = "north-america.pool.ntp.org";  // Regional server pool.
// const char timeServer[] = "oceania.pool.ntp.org";    // Regional server pool.
// const char timeServer[] = "south-america.pool.ntp.org";  // Regional server pool.
// const char timeServer[] = "time.nist.gov";     // Original example target server (least preferred).

const uint8_t SLEEP_SECS = 15;      // Number of seconds to sleep between queries to the time
            // server. Please don't set this any lower than 10 unless
            // timeServer[] is a local NTP server on -your- network.

// Temperature min, max, … value
const uint8_t MIN_REQUERED_TEMPERATURE = 0;
const uint8_t MAX_REQUERED_TEMPERATURE = 30;
const float CHANGE_TEMPERATURE = 0.5;
const float DEFAULT_REQUIRED_TEMPERATURE = 20;