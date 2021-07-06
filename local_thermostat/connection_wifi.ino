/*
 * Settings WiFi connection
 * MQTT via WiFi
*/
#include <esp_wifi.h>
#include <WiFi.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

void WiFiEvent(WiFiEvent_t event);
void onMqttDisconnectWifi(AsyncMqttClientDisconnectReason reason);
void onMqttMessageWifi(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

AsyncMqttClient asyncMqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void connectToWifi() 
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqttWifi() 
{
  Serial.println("Connecting to MQTT...");
  asyncMqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) 
{
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch(event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      isConnection = true;
      connectToMqttWifi();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      isConnection = false;
      xTimerStop(mqttReconnectTimer, 0); // ensure we don't reconnect to MQTT while reconnecting to Wi-Fi
      xTimerStart(wifiReconnectTimer, 0);
      break;
  }
}

void onMqttConnectWifi(bool sessionPresent) 
{
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  
  setSubscribe();
}

void onMqttDisconnectWifi(AsyncMqttClientDisconnectReason reason) 
{
  Serial.println("Disconnected from MQTT.");
  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribeWifi(uint16_t packetId, uint8_t qos) 
{
  Serial.println("Subscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
  Serial.print("  qos: ");
  Serial.println(qos);
}

void onMqttUnsubscribeWifi(uint16_t packetId) 
{
  Serial.println("Unsubscribe acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttPublishWifi(uint16_t packetId) 
{
  Serial.print("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void onMqttMessageWifi(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) 
{
  parseTopic(topic, payload);
}

void setupWifi() 
{
  //WiFi.mode(WIFI_STA);
  //esp_wifi_set_mac(WIFI_IF_STA, MAC_ADDRESS);

  //if (!WiFi.config(IP, GATEWAY, SUBNET_MASK, DNS_SERVER)) {
  // Serial.println("STA Failed to configure");
  //   }
  //Serial.println(WiFi.localIP());
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqttWifi));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  asyncMqttClient.onConnect(onMqttConnectWifi);
  //asyncMqttClient.onDisconnect(onMqttDisconnect);
  asyncMqttClient.onSubscribe(onMqttSubscribeWifi);
  //asyncMqttClient.onUnsubscribe(onMqttUnsubscribe);
  asyncMqttClient.onMessage(onMqttMessageWifi);
  asyncMqttClient.onPublish(onMqttPublishWifi);
  asyncMqttClient.setServer(MQTT_HOST, MQTT_PORT);
  // If your broker requires authentication (username and password), set them below
  asyncMqttClient.setCredentials(MQTT_USER, MQTT_PASSWORD);

  
  connectToWifi();
 }
