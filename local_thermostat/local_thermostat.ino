
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "local_config.h"  // <--- Change settings for YOUR network here.

#define _cs   5   // 3 goes to TFT CS
#define _dc   4   // 4 goes to TFT DC
#define _mosi 23  // 5 goes to TFT MOSI
#define _sclk 18  // 6 goes to TFT SCK/CLK
#define _rst  22  // ESP RST to TFT RESET
#define _miso     // Not connected
//       3.3V     // Goes to TFT LED  
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd        

// Use hardware SPI (on ESP D4 and D8 as above)
//Adafruit_ILI9341 tft = Adafruit_ILI9341(_CS, _DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);
//Adafruit_ILI9341_Albert tft = Adafruit_ILI9341_Albert(_cs, _dc, _mosi, _sclk, _rst);

float requiredTemperature = DEFAULT_REQUIRED_TEMPERATURE;
float oldRequiredTemperature = 0;
bool isTurnOnDisplay = false;

bool isNewTemperature = false;


void setup() 
{ 
  tempSensorSetup();
  buttonsSetup(); 
  timersSetup();  
  TftSetup();
  MqttSetup();
}

void loop() 
{
  loopTimers();
  loopButton();
  MqttLoop();
  if(isNewTemperature)
  {
    float temperature = getTemperature();
    writeTemperature(temperature, 20, 80, ILI9341_RED, 6);
    SendTemperature(temperature);
  }
}
