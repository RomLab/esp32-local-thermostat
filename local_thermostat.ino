
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define _cs   0   // 3 goes to TFT CS
#define _dc   2   // 4 goes to TFT DC
#define _mosi 14  // 5 goes to TFT MOSI
#define _sclk 12  // 6 goes to TFT SCK/CLK
#define _rst  13  // ESP RST to TFT RESET
#define _miso     // Not connected
//       3.3V     // Goes to TFT LED  
//       5v       // Goes to TFT Vcc
//       Gnd      // Goes to TFT Gnd        

// Use hardware SPI (on ESP D4 and D8 as above)
//Adafruit_ILI9341 tft = Adafruit_ILI9341(_CS, _DC);
// If using the breakout, change pins as desired
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);


long last_time = 0;
float requireTemperature = 20;
void setup() 
{
  TftSetup();
  Ds18b20Setup();
  MqttSetup();

}

void loop() 
{
    MqttLoop();
    long now = millis();
    if (now - last_time > 30000) 
    {
      float temp = GetDs18b20Temp();
      SendTemperature(temp);
      WriteTemperature(temp, 16, 80, ILI9341_RED, 6);
      last_time = now;
    }
    ChangeRequireTemperature();
}
