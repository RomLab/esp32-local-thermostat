volatile int interruptCounter = 0;
volatile int interruptCounterTemp = 0;

 
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


hw_timer_t * timerTemp = NULL;
portMUX_TYPE timerMuxTemp = portMUX_INITIALIZER_UNLOCKED;

bool isEnableTimerTurnOffDisplay = false;

void IRAM_ATTR onTimer() 
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&timerMux); 
}

void IRAM_ATTR onTimerTemp() 
{
  portENTER_CRITICAL_ISR(&timerMuxTemp);
  interruptCounterTemp++;
  portEXIT_CRITICAL_ISR(&timerMuxTemp); 
}

void timersSetup() 
{
  startTimerForTurnOffDisplay();
  startTimerForSampleTemp();
}

void loopTimers()
{
  // Serial.println("Test" + interruptCounter);
  if (interruptCounter == 30) 
  {
    portENTER_CRITICAL(&timerMux);
    //Serial.println("Turn OFF");
    stopTimerForTurnOffDisplay();
    turnOffDisplay();
    SendRequiredTemperature(requiredTemperature);
    interruptCounter = 0;
    portEXIT_CRITICAL(&timerMux);
  }
  
  if (interruptCounterTemp == 30) 
  { 
    portENTER_CRITICAL(&timerMuxTemp);
    isNewTemperature = true;
    interruptCounterTemp = 0;
    portEXIT_CRITICAL(&timerMuxTemp);
   }
   else
   {
    isNewTemperature = false;
   }
}

void startTimerForTurnOffDisplay()
{
  interruptCounter = 0;
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void stopTimerForTurnOffDisplay()
{
  timerAlarmDisable(timer);   
  timerDetachInterrupt(timer);
  timerEnd(timer);
  timer = NULL;
}

void startTimerForSampleTemp()
{
  interruptCounterTemp = 0;
  timerTemp = timerBegin(1, 80, true);
  timerAttachInterrupt(timerTemp, &onTimerTemp, true);
  timerAlarmWrite(timerTemp, 1000000, true);
  timerAlarmEnable(timerTemp);
}

void stopTimerForSampleTemp()
{
  timerAlarmDisable(timerTemp);   
  timerDetachInterrupt(timerTemp);
  timerEnd(timerTemp);
  timerTemp = NULL;
}
