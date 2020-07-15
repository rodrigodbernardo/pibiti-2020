#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
#include "MPU6050.h"

#define SDA D6
#define SCL D5

ESP8266WiFiMulti wifiMulti;

MPU sensor;

void setup(){
    Serial.begin(115200);
    Wire.begin(SDA, SCL);

    setupWiFi();
    sensor.setup();
}

void loop(){

}

///////////
///////////

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
