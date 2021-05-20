#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(26);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void Ds18b20Setup() 
{
  //Serial.begin(115200);
  sensors.begin();
}

float GetDs18b20Temp() {
  
  sensors.requestTemperatures(); 
  //Serial.println(sensors.getTempCByIndex(0));
  float correction = 1.5;
  return (sensors.getTempCByIndex(0)-correction);
}
