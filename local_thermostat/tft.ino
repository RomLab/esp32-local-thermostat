// Fonts
#include "fonts/Calibri40.h"
#include "fonts/Calibri60.h"
#include "fonts/Calibri80.h"

// The font names are arrays references, thus must NOT be in quotes ""
#define CURRENT_TEMPERATURE Calibri80
#define REQUIRED_TEMPERATURE Calibri60
#define USER_MESSAGE Calibri40

// Scrolled text
String oldScrolledText;
uint8_t counterOfScroller = 0;

void tftSetup() 
{
  // Sets pin for turn on display
  pinMode(21, OUTPUT);
  
  tft.begin();
  tft.setRotation(1);
  
  tft.fillScreen(TFT_BLACK);

  writeOnDisplay(getNumberWithOnDecimalPlace(String(requiredTemperature)), 160, 140, TFT_GREEN, 2);
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


void writeOnDisplay(String text, int positionX, int positionY, uint16_t colorText, int positionLine) 
{
  String tempText = text;
  if(positionLine == 1)
  {
      tft.loadFont(CURRENT_TEMPERATURE);
      // Overprint with a filled rectangle
      tft.fillRect(0, positionY, 320, 80, TFT_BLACK); 
      tempText.replace('.', ',');
      tempText += " °C";
  }
  else if(positionLine == 2)
  {
     tft.loadFont(REQUIRED_TEMPERATURE); 
     // Overprint with a filled rectangle
     tft.fillRect(0, positionY, 320, 60, TFT_BLACK); 
     tempText.replace('.', ',');
     tempText += " °C";
  }
  else
  {
    tft.loadFont(USER_MESSAGE); 
    // Overprint with a filled rectangle
    tft.fillRect(0, positionY, 320, 60, TFT_BLACK); 
    if(tempText.length() > 18)
    {
      isEnableRotationUserMessage = true;
      userMessage = tempText;
      return;
    }
    else
    {
      isEnableRotationUserMessage = false;
    }
  }

  tft.setTextColor(colorText, TFT_BLACK);
  // Value font = 1 is not using
  tft.drawCentreString(tempText, positionX, positionY, 1); 
}


void scrollTextOnDisplay(String userMassage)
{
  String tempText = userMassage;

  if (counterOfScroller++ >= tempText.length())
  {
    counterOfScroller = 1;
  }
   
  setText(205, oldScrolledText, TFT_WHITE);
  tempText = getScrolledText(tempText, counterOfScroller);
  setText(205, tempText, TFT_WHITE);
  oldScrolledText = tempText;

  delay(200);
}

String getScrolledText(String text, uint8_t positionText)
{
   String scrolledText = "";
   // Construct the string to display for this iteration
   for (uint8_t index = 0; index < text.length(); index++)
   {
     scrolledText += text.charAt((positionText + index) % text.length());
   }
    
   return scrolledText;
}

void setText(uint8_t row, String text, uint16_t colorText)
{
    tft.loadFont(USER_MESSAGE); 
    tft.setTextColor(colorText, TFT_BLACK);
    tft.setCursor(0, row);
    // Overprint with a filled rectangle
    tft.fillRect(0, row, 320, 60, TFT_BLACK); 
    tft.print(text);
}
