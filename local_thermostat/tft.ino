/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

void tftSetup() 
{
  // Turn on Display 
  pinMode(21, OUTPUT);
  
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5, 1);
  turnOnDisplay();
}

void firstTurnOnDisplay()
{
  digitalWrite(21, HIGH);
}

void turnOnDisplay()
{
   isTurnOnDisplay = true;
   digitalWrite(21, HIGH);
}

void turnOffDisplay()
{
   isTurnOnDisplay = false;
   digitalWrite(21, LOW);
}

void writeTemperature(float temperatureC, int positionX, int positionY, uint16_t colorText, int sizeFont, int positionLine) 
{
  bool clearTextForTemp = (temperatureC > 10 && oldTemperature <= 10) || (temperatureC < 10 && oldTemperature >= 10);
  bool clearTextForRequiredTemp = (temperatureC > 10 && oldRequiredTemperature <= 10) || (temperatureC < 10 && oldRequiredTemperature >= 10);
  // Clear text
  if((clearTextForTemp && positionLine == 0) || (clearTextForRequiredTemp && positionLine == 1))
  {
    tft.setCursor(positionX, positionY);
    tft.setTextSize(sizeFont); 
    tft.setTextColor(colorText, ILI9341_BLACK);
    tft.print("        ");
  }

  // Move position x
  int tempPositionX = positionX;
  if(temperatureC < 10)
  {
     tempPositionX +=18+sizeFont;
  }
   
  tft.setCursor(tempPositionX, positionY);
  tft.setTextSize(sizeFont); 
  tft.setTextColor(colorText, ILI9341_BLACK);
  String stringTemperatureC = String(temperatureC); 
  tft.println(stringTemperatureC + " " +(char)247 +"C");
}
