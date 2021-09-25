#include "time.h"

const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;
int oldMinute = -1;

void ntpSetup()
{
  configTime(gmtOffset_sec, daylightOffset_sec, timeServer);
}

void ntpLoop()
{
  getActualTime();
}

void getActualTime()
{
  struct tm timeinfo;
  if(getLocalTime(&timeinfo))
  {
    char actualMinute[3];
    strftime(actualMinute,3, "%M", &timeinfo);
    int minute = (int)actualMinute;
    
    if(oldMinute != minute)
    {
      char actualTime[6];
      strftime(actualTime, 6, "%H:%M", &timeinfo);
      sendActualTime(String(actualTime));
      oldMinute = minute;
    }
  }
}
