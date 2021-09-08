// MQTT topic
String samePrefix = "home/"+numberOfFloor+"/"+roomName;
String topicFromSystem = samePrefix+"/required-temperature-from-system";
String topicFromDevice = samePrefix+"/required-temperature-from-device";
String topicTemperature = samePrefix+"/temperature";
String mqttUserMessage = "home/user-message";

// For MQTT Ethernet
char data[100];

void setSubscribe()
{  
  if(typeOfConnection == WIFI)
  {
    asyncMqttClient.subscribe(topicFromSystem.c_str(), 2); 
    asyncMqttClient.subscribe(mqttUserMessage.c_str(), 2);
  }
  else
  {
    mqttClientEthernet.subscribe(topicFromSystem.c_str(), 1);
    mqttClientEthernet.subscribe(mqttUserMessage.c_str(), 1);
  }
}

void sendTemperature(float temperature) 
{
  if(typeOfConnection == WIFI)
  {
    asyncMqttClient.publish(topicTemperature.c_str(), 2, true, String(temperature).c_str());  
  }
  else
  {
    sprintf(data, "%f", temperature);
    mqttClientEthernet.publish(topicTemperature.c_str(), data);
  }
}

void sendRequiredTemperature(float requiredTemperature) 
{
  if(typeOfConnection == WIFI)
  {
     asyncMqttClient.publish(topicFromDevice.c_str(), 2, true, String(requiredTemperature).c_str()); 
  }
  else
  {
    sprintf(data, "%f", requiredTemperature);
    mqttClientEthernet.publish(topicFromDevice.c_str(), data);
  }
}

void parseTopic(char* topic, String payload)
{

  String topicString = String(topic);
  if(topicString == mqttUserMessage)
  {
    String stringPayload = String(payload);
    userMessage = stringPayload;
    isNewUserMessage = true;
  }
  
  if(topicString == topicFromSystem)
  {
    String stringPayload = String(payload);
    float value = stringPayload.toFloat();
    int intValue = (int)( value * 10);
       
    oldRequiredTemperature = requiredTemperature;
    requiredTemperature = (float)intValue/10;
    isNewRequiredTemperatureFromSystem = true;
  }
}
