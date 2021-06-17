
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
#define ETHERNET_PIN_RST       (27)        // Tie the Wiz820io/W5500 reset pin to ESP32 GPIO26 pin.

// Use hardware SPI (on ESP D4 and D8 as above)
//Adafruit_ILI9341 tft = Adafruit_ILI9341(_CS, _DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(DISPLAY_PIN_SPI_CS, DISPLAY_PIN_SPI_DC, DISPLAY_PIN_SPI_MOSI, DISPLAY_PIN_SPI_SCLK, DISPLAY_PIN_SPI_RST);

float requiredTemperature = DEFAULT_REQUIRED_TEMPERATURE;
float oldRequiredTemperature = 0;
bool isTurnOnDisplay = false;

bool isNewTemperature = false;
bool isConnectedEthernet = false;


void setup() 
{ 
    mqttSetup();
  tempSensorSetup();
  buttonsSetup(); 
  timersSetup();  
  tftSetup();

}

void loop() 
{
  loopTimers();
  loopButton();
  mqttLoop();
  if(isNewTemperature)
  {
    float temperature = getTemperature();
    writeTemperature(temperature, 20, 80, ILI9341_RED, 6);
    if(isConnectedEthernet)
    {
       SendTemperature(temperature);
    }
  }

  if(!isConnectedEthernet)
  {
     mqttSetup();
     timersSetup();
  }
  

}
