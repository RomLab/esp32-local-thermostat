unsigned long lastInterruptPlusButton;
unsigned long lastInterruptPlusButtonTurnOnDisplay;
unsigned long lastInterruptMinusButton;
unsigned long lastInterruptMinusButtonTurnOnDisplay;
unsigned long lastInterruptMenuButton;
unsigned long lastInterruptMenuButtonTurnOnDisplay;
uint8_t const NEXT_INTERRUPT_BUTTON = 15; // ms
uint8_t const NEXT_INTERRUPT_BUTTON_TURN_ON_DISPLAY = 200; // ms

volatile bool pressedPlusButton = false;
volatile bool pressedMinusButton = false;
volatile bool pressedMenuButton = false;


void IRAM_ATTR pressPlusTemp() 
{
  pressedPlusButton = true;
}

void IRAM_ATTR pressMinusTemp() 
{
  pressedMinusButton = true;
}

void IRAM_ATTR pressMenu() 
{
  pressedMenuButton = true;
}

void buttonsSetup() 
{
  pinMode(32, INPUT);
  attachInterrupt(digitalPinToInterrupt(32), pressPlusTemp, FALLING);

  pinMode(25, INPUT);
  attachInterrupt(digitalPinToInterrupt(25), pressMinusTemp, FALLING);

  pinMode(33, INPUT);
  attachInterrupt(digitalPinToInterrupt(33), pressMenu, FALLING);
}

void loopButton()
{
  if(pressedPlusButton)
  {
    pressedPlusButton = false;
    if(millis() - lastInterruptPlusButton > NEXT_INTERRUPT_BUTTON)
    {
      if(isTurnOnDisplay && millis() - lastInterruptPlusButtonTurnOnDisplay > NEXT_INTERRUPT_BUTTON_TURN_ON_DISPLAY)
      {
        startTimerForTurnOffDisplay();   
        oldRequiredTemperature =  requiredTemperature;
       // requiredTemperature += CHANGE_TEMPERATURE;
        changeRequredTemperature(true);
        writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5);
        lastInterruptPlusButton = millis();
      }
      else
      {
        turnOnDisplay();
        startTimerForTurnOffDisplay(); 
        lastInterruptPlusButtonTurnOnDisplay = millis();
      }
    }
  }
  
  if(pressedMinusButton)
  {
    pressedMinusButton = false;
    if(millis() - lastInterruptMinusButton > NEXT_INTERRUPT_BUTTON)
    {
  
      if(isTurnOnDisplay && millis() - lastInterruptMinusButtonTurnOnDisplay > NEXT_INTERRUPT_BUTTON_TURN_ON_DISPLAY)
      {
        startTimerForTurnOffDisplay();   
        oldRequiredTemperature =  requiredTemperature;
        //requiredTemperature -= CHANGE_TEMPERATURE;
        changeRequredTemperature(false);
        writeTemperature(requiredTemperature, 40, 135, ILI9341_GREEN, 5);
        lastInterruptMinusButton = millis();
      }
      else
      {
        turnOnDisplay();
        startTimerForTurnOffDisplay(); 
        lastInterruptMinusButtonTurnOnDisplay = millis();
      }
    }
  }
  
  if(pressedMenuButton)
  {
    pressedMenuButton = false;
    if(millis() - lastInterruptMenuButton > NEXT_INTERRUPT_BUTTON)
    {
    
      if(isTurnOnDisplay && millis() - lastInterruptMenuButtonTurnOnDisplay > NEXT_INTERRUPT_BUTTON_TURN_ON_DISPLAY)
      {
        startTimerForTurnOffDisplay();   
        lastInterruptMenuButton = millis();
      }
      else
      {
        turnOnDisplay();
        startTimerForTurnOffDisplay(); 
        lastInterruptMenuButtonTurnOnDisplay = millis();
      }
    }
  }
}

void changeRequredTemperature(bool isIcrement)
{
  if(isIcrement)
  {
    float tempRequiredTemperature = requiredTemperature + CHANGE_TEMPERATURE;   
    if(tempRequiredTemperature <= MAX_REQUERED_TEMPERATURE)
    {
       requiredTemperature += CHANGE_TEMPERATURE;
    }    
  }
  if(!isIcrement)
  {
    float tempRequiredTemperature = requiredTemperature - CHANGE_TEMPERATURE;
    if(tempRequiredTemperature >= MIN_REQUERED_TEMPERATURE)
    {
       requiredTemperature -= CHANGE_TEMPERATURE;
    }  
  }
}