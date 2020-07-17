#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <Wire.h>

#include <vector>

#include "lib-MPU.h"
#include "lib-nodemcu.h"

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

  //  1
  //verifica wifi
    //se o wifi esta desconectado, tenta realizar conexao por 1 minuto

  //tenta conectar ao broker
    //caso conectado, espera por um comando.

  //verifica o comando
    //caso seja 'captura em lote',
      //  2
      //receber detalhes da captura
      //conectar ao firebase (ordem pode ser invertida com o proximo passo)
      //realizar captura
      //transferir dados ao firebase
      //enviar status por MQTT
      //deve continuar?
        //caso positivo, retornar ao ponto '2'
        //caso negativo, fechar conexao com o broker e retornar ao ponto '1'
      
    //caso seja 'analise em tempo real',
      //  3
      //realizar captura
      //transferir captura (talvez por mqtt)
      //verificar se deve continuar
        //caso positivo, retornar ao ponto '3'
        //caso negativo, fechar conexao com o broker e retornar ao ponto '1'
   
}

///////////
///////////
