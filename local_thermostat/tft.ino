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



// GPIO where the DS18B20 is connected to
//float oldTemepratureC = 0;





// One-wire bus
// Setup a oneWire instance to communicate with any OneWire devices
//OneWire oneWire(4);
// Pass our oneWire reference to Dallas Temperature sensor 
//DallasTemperature sensors(&oneWire);



void TftSetup() {
  // Turn on Display 
  pinMode(21, OUTPUT);
  //Serial.begin(9600);
  
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  // Start the DS18B20 sensor
  sensors.begin();
  


 
  writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5);
 
 
  // read diagnostics (optional but can help debug problems)
 /* uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);

  Serial.print(F("Text                     "));
  Serial.println(testText());
  delay(3000);
*/

  turnOnDisplay();
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



// TftLoop(void) {
 
   
  // CheckTemperature();
  // ChangeRequireTemperature();
  
//}

/*void CheckTemperature() {
   float temperatureC = ReadTemeperature();
  
   if (oldTemepratureC != temperatureC)
   {
       WriteTemperature(temperatureC, 0, 100, ILI9341_RED, 5);
   }
   
   oldTemepratureC = temperatureC;
}*/



/*float ReadTemeperature() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  return temperatureC;
}*/

void writeTemperature(float temperatureC, int positionX, int positionY, uint16_t colorText, int sizeFont) {

  // Clear text
  tft.setCursor(positionX, positionY);
  tft.setTextSize(sizeFont); 
  tft.setTextColor(colorText, ILI9341_BLACK);

  tft.print("        ");

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

  
 /* tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;*/
}
