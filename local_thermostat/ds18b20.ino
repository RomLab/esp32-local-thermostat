#include <OneWire.h>
#include <DallasTemperature.h>

// GPIO where the DS18B20 is connected to

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(4);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void Ds18b20Setup() 
{

  sensors.begin();
}

float GetDs18b20Temp() {
  sensors.requestTemperatures(); 
  return sensors.getTempCByIndex(0);
}
