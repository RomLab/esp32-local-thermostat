
#include <SPI.h>
#include <TFT_eSPI.h> 

#include "local_config.h"  // <--- Change settings for YOUR network here.

// SPI pins for display
// Define in TFT_eSPI, User_Setup.h
//#define DISPLAY_PIN_SPI_CS    (5)
//#define DISPLAY_PIN_SPI_DC    (4)
//#define DISPLAY_PIN_SPI_MOSI  (23)
//#define DISPLAY_PIN_SPI_SCLK  (18)
//#define DISPLAY_PIN_SPI_RST   (22)
//#define DISPLAY_PIN_SPI_MISO     // Not connected


// SPI for Ethernet
#define ETHERNET_PIN_SPI_CS    (15)
#define ETHERNET_PIN_SPI_MOSI  (13)
#define ETHERNET_PIN_SPI_MISO  (12)
#define ETHERNET_PIN_SPI_SCK   (14)
#define ETHERNET_PIN_RST       (27) // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.


TFT_eSPI tft = TFT_eSPI();

// Icons of connection
extern uint8_t online[];
extern uint8_t offline[];
extern uint8_t connectionOfMQTTBroker[];

// Temperatures
float requiredTemperature = DEFAULT_REQUIRED_TEMPERATURE;
float oldRequiredTemperature = 0;
float oldTemperature = 0;
bool isNewRequiredTemperatureFromSystem = false;
bool isNewTemperature = false;

// Connection
bool isConnection = false;
bool isConnectionOfMQTTBroker = false;

bool isTurnOnDisplay = false;

// User message
String userMessage;
bool isNewUserMessage = false;
bool isEnableRotationUserMessage = false;

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
  
  if(isNewUserMessage)
  {
     writeOnDisplay(userMessage, 160, 205, TFT_WHITE, 3);
     isNewUserMessage= false;
  }

  if(isEnableRotationUserMessage)
  {
     scrollTextOnDisplay(userMessage);
  }
   
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

  if(isNewTemperature && !isTurnOnDisplay)
  {
    float temperature = getTemperature();
    writeOnDisplay(getNumberWithOnDecimalPlace(String(temperature)), 160, 60, ILI9341_RED, 1);
    if(isConnection)
    {
      sendTemperature(temperature);
    }
  }
  
  if(isNewRequiredTemperatureFromSystem)
  {
    writeOnDisplay(getNumberWithOnDecimalPlace(String(requiredTemperature)), 160, 140, ILI9341_GREEN, 2);
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
