#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

#include "lib-nodemcu.h"

void Nodemcu::setupWiFi(ESP8266WiFiMulti wifiMulti)
{
  // ----> A FAZER
  //  ADICIONAR FUNÇÃO WPS.

  while (wifiMulti.run() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(SSID_01, PASS_01);
    Serial.println("Trying to connect to WiFi");
    delay(500);
  }
  Serial.println("\nWiFi connected successfully!");
  Serial.println(WiFi.localIP());

  /*
  if (wifiMulti.run() != WL_CONNECTED) {

    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(SSID_01, PASS_01);

    Serial.print("\n\nTrying to connect to WiFi");
    while (wifiMulti.run() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("\n\nWiFi connected successfully!");
    Serial.println(WiFi.localIP());
  }
*/
}

void Nodemcu::setupOTA()
{
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
    {
      type = "sketch";
    }
    else
    { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR)
    {
      Serial.println("Auth Failed");
    }
    else if (error == OTA_BEGIN_ERROR)
    {
      Serial.println("Begin Failed");
    }
    else if (error == OTA_CONNECT_ERROR)
    {
      Serial.println("Connect Failed");
    }
    else if (error == OTA_RECEIVE_ERROR)
    {
      Serial.println("Receive Failed");
    }
    else if (error == OTA_END_ERROR)
    {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("OTA Ready.");
}
void Nodemcu::setupMQTT(PubSubClient MQTT, char *deviceID)
{
  while (!MQTT.connected())
  {
    Serial.println("Trying to connect to the Broker.");
    if (MQTT.connect(deviceID))
    {
      Serial.print("\nBroker connected successfully!");
    }
    delay(5000);
  }
}

//principal função do programa
void Nodemcu::inputMQTT(char* topic, byte* payload, unsigned int length){

}
