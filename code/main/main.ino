#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <Wire.h>

#include <vector>

#include "lib-MPU.h"
#include "lib-nodemcu.h"

#define SDA D6
#define SCL D5

using namespace std;

////Constantes e variaveis gerais

const long loopInterval = 1000;
unsigned long prevTime = 0;

//// DADOS MQTT

const char* server    = "iot.eclipse.org";
const int   port      = 1883;

#define deviceID  "node_01"
#define topic     "topico_01"

////

//vector <vector<int>> myvector;

////Objetos

ESP8266WiFiMulti wifiMulti;
MPU sensor;
Nodemcu nodemcu;

WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);

void setup(){
    Serial.begin(115200);
    Wire.begin(SDA, SCL);
    nodemcu.setupWiFi(wifiMulti);
    nodemcu.setupOTA();
    sensor.setup();

    MQTT.setServer(server, port);
    MQTT.setCallback(nodemcu.inputMQTT);
}

void loop(){

  //checa as conexoes
  nodemcu.setupWiFi(wifiMulti);
  nodemcu.setupMQTT(MQTT);

  //aguarda OTA ou comando MQTT
  ArduinoOTA.handle();
  MQTT.loop();
/*
  unsigned long currTime = millis();

  if(currTime - prevTime >= loopInterval){
    prevTime = currTime;

    ArduinoOTA.handle();
    MQTT.loop();
  }
*/
  
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
