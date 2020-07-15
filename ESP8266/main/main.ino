#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>

#include <Wire.h>

#include "MPU6050.h"
#include "nodemcu.h"

#define SDA D6
#define SCL D5

ESP8266WiFiMulti wifiMulti;

MPU sensor;
Nodemcu nodemcu;

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Wire.begin(SDA, SCL);

    //setupWiFi(wifiMulti);
    nodemcu.setupWiFi(wifiMulti);
    nodemcu.setupOTA();
    sensor.setup();
}

void loop(){
  ArduinoOTA.handle();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
}

///////////
///////////
/*
void setupWiFi(){
    // ----> A FAZER
    //  ADICIONAR FUNÇÃO WPS.

    WiFi.mode(WIFI_STA);
    wifiMulti.addAP("FLAVIO_02","8861854611");

    Serial.print("\n\nTrying to connect to WiFi");
    while(wifiMulti.run() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n\nWiFi connected successfully!");
    Serial.println(WiFi.localIP());
}
*/
