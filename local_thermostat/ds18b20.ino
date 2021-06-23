#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(26);
DallasTemperature sensors(&oneWire);

// 3 sample
int temperatures[3];

void tempSensorSetup() 
{
  sensors.begin();
}

float getTemperature() 
{
  float correction = 3.6;  
  float sumTemperatures = 0;
  for (int index = 0; index < 3; index++)
  {
      sensors.requestTemperatures(); 
      sumTemperatures += sensors.getTempCByIndex(0) - correction;
  } 
  float avarageTemperature = ((float)sumTemperatures) / 3 ;
  float roundTemperature = round((avarageTemperature) * 10) / 10;
  oldTemperature = roundTemperature; 
  return (roundTemperature);
}
