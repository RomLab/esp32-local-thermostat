// MQTT topic
String samePrefix = "home/first-floor/"+roomName;
String topicFromSystem = samePrefix+"/required-temperature-from-system";
String topicFromDevice = samePrefix+"/required-temperature-from-device";
String topicTemperature = samePrefix+"/temperature";

// For MQTT Ethernet
char data[100];

void setSubscribe()
{
  if(typeOfConnection == WIFI)
  {
    asyncMqttClient.subscribe(getTopicArray(topicFromSystem), 2); 
  }
  else
  {
    mqttClientEthernet.subscribe(getTopicArray(topicFromSystem), 1);
  }
}

void sendTemperature(float temperature) 
{
  if(typeOfConnection == WIFI)
  {
    asyncMqttClient.publish(getTopicArray(topicTemperature), 2, true, String(temperature).c_str());  
  }
  else
  {
    sprintf(data, "%f", temperature);
    mqttClientEthernet.publish(getTopicArray(topicTemperature), data);
  }
}

void sendRequiredTemperature(float requiredTemperature) 
{
  if(typeOfConnection == WIFI)
  {
     asyncMqttClient.publish(getTopicArray(topicFromDevice), 2, true, String(requiredTemperature).c_str()); 
  }
  else
  {
    sprintf(data, "%f", requiredTemperature);
    mqttClientEthernet.publish(getTopicArray(topicFromDevice), data);
  }
}

void parseTopic(char* topic, char* payload)
{
  if(strcmp(topic, getTopicArray(topicFromSystem)) == 0)
  {
    String stringPayload = String(payload);
    float value = stringPayload.toFloat();
    int intValue = (int)( value * 10);
       
    oldRequiredTemperature = requiredTemperature;
    requiredTemperature = (float)intValue/10;
    isNewRequiredTemperatureFromSystem = true;
  }
}

char* getTopicArray(String topic)
{
  int lengthTopic = topic.length() + 1;    
  char * topicArray = (char *) malloc (lengthTopic);
  topic.toCharArray(topicArray, lengthTopic);
  return topicArray;
}
