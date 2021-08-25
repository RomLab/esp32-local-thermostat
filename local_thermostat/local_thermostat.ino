
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "local_config.h"  // <--- Change settings for YOUR network here.

// SPI pins for display
#define DISPLAY_PIN_SPI_CS    (5)
#define DISPLAY_PIN_SPI_DC    (4)
#define DISPLAY_PIN_SPI_MOSI  (23)
#define DISPLAY_PIN_SPI_SCLK  (18)
#define DISPLAY_PIN_SPI_RST   (22)
//#define DISPLAY_PIN_SPI_MISO     // Not connected


// SPI for Ethernet
#define ETHERNET_PIN_SPI_CS    (15)
#define ETHERNET_PIN_SPI_MOSI  (13)
#define ETHERNET_PIN_SPI_MISO  (12)
#define ETHERNET_PIN_SPI_SCK   (14)
#define ETHERNET_PIN_RST       (27) // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.

Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_PIN_SPI_CS, DISPLAY_PIN_SPI_DC, DISPLAY_PIN_SPI_MOSI, DISPLAY_PIN_SPI_SCLK, DISPLAY_PIN_SPI_RST);

// Icons of connection
extern uint8_t online[];
extern uint8_t offline[];
extern uint8_t connectionOfMQTTBroker[];


float requiredTemperature = DEFAULT_REQUIRED_TEMPERATURE;
float oldRequiredTemperature = 0;
float oldTemperature = 0;
bool isTurnOnDisplay = false;

bool isNewTemperature = false;
bool isConnection = false;
bool isConnectionOfMQTTBroker = false;
bool isTurnOffDisplay = false;
bool isNewRequiredTemperatureFromSystem = false;


void setup() 
{ 
  Serial.begin(115200);
  tempSensorSetup();
  buttonsSetup(); 
  timersSetup();  
  tftSetup();

  if(typeOfConnection == WIFI)
  {
    setupWifi();
  }
  else
  {
    setupEthernet();
  }
}

void loop() 
{
  loopTimers();
  loopButton();
  
  if(!isConnection)
  {
    if(typeOfConnection == ETHERNET)
    {
      setupEthernet();
    }
    // WiFi have custom loop
  }

  if(typeOfConnection == ETHERNET)
  {
    mqttLoopEthernet();
  }


  setIconOfConnection();

  if(isNewTemperature && isTurnOffDisplay)
  {
    float temperature = getTemperature();
    writeTemperature(temperature, 20, 80, ILI9341_RED, 6, 0);
    if(isConnection)
    {
      sendTemperature(temperature);
    }
  }
  
  if(isNewRequiredTemperatureFromSystem)
  {
    writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5, 1);
    isNewRequiredTemperatureFromSystem = false;
  }
}

void setIconOfConnection()
{
  if(isConnection)
  {
    tft.drawBitmap(0, 0, online, 20, 20, ILI9341_GREEN);
    
    if(isConnectionOfMQTTBroker)
    {
      tft.drawBitmap(25, 0, connectionOfMQTTBroker, 20, 20, ILI9341_GREEN);
    }
    else
    {
      tft.drawBitmap(25, 0, connectionOfMQTTBroker, 20, 20, ILI9341_RED);
    }
  }
  else
  {
    tft.drawBitmap(0, 0, online, 20, 20, ILI9341_RED);
    tft.drawBitmap(25, 0, connectionOfMQTTBroker, 20, 20, ILI9341_RED);
  }
}
