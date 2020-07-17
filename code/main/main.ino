#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <Wire.h>

#include <vector>

#include "MPU6050.h"
#include "nodemcu.h"

#define SDA D6
#define SCL D5

using namespace std;

vector <vector<int>> myvector;

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
   
}

///////////
///////////
