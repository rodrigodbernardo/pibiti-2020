#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
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
bool liveFlag = 0;



//// DADOS MQTT

const char* inTopic     = "rdba_cmd";
const char* outTopic    = "rdba_live";
const char* server    = "broker.hivemq.com";
const int   port      = 1883;

//// DADOS DE CAPTURA
int capt;
int samp;

////

//vector <vector<int>> myvector;

////Objetos

ESP8266WiFiMulti wifiMulti;
MPU sensor;
Nodemcu nodemcu;
StaticJsonDocument <200> data;

WiFiClient wifiClient;
PubSubClient MQTT(wifiClient);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  nodemcu.setupWiFi(wifiMulti);

  nodemcu.setupOTA();
  sensor.setup();

  MQTT.setServer(server, port);
  MQTT.setCallback(inputMQTT);
}

void loop() {

  if (!MQTT.connected()) {
    setupMQTT();
  }

  //aguarda OTA ou comando MQTT
  ArduinoOTA.handle();
  MQTT.loop();

  //só entrará nessa rotina a cada 'loopInterval' de tempo. 
  unsigned long curMillis = millis();
  if (curMillis - prevMillis >= loopInterval) {
    prevMillis = curMillis;
    if (liveFlag) {
      Serial.println("Esta é uma captura.");
      MQTT.publish(outTopic, "Essa é uma captura");
      //delay(100);
    }
  }

  //  1
  //verifica wifi
  //se o wifi esta desconectado, tenta realizar conexao

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

void inputMQTT(char* topic, byte* payload, unsigned int length) {
  String msg;

  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    msg += c;
  }

  Serial.println("Input: " + msg);
  deserializeJson(data, msg);

  /*
      A mensagem recebida tem o formato:
      {"cmd":"xxxx","num_capt":"yyyy","num_samp":"zzzz"}
  */

  if (data["cmd"] == "cmd_capt") {
    liveFlag = 0;
    Serial.println("\nCapture Mode.");
    
    Serial.print("Num. of captures: ");   Serial.println(data["nCapture"].as<String>());
    Serial.print("Num. of samples:  ");   Serial.println(data["nSample"].as<String>());
    Serial.print("Sample rate (ms):  ");  Serial.println(data["nSample"].as<String>());

    int nCapture   = data["nCapture"];
    int nSample    = data["nSample"];
    int sampleRate = data["sampleRate"];

    MPU.capture(nCapture,nSample,sampleRate);
  }
  else if (data["cmd"] == "cmd_live") {
    liveFlag = 1;
    Serial.println("\nLive Mode");
  }
  else {
    liveFlag = 0;
    Serial.println("Comando desconhecido. Tente novamente.\n");
  }
}

void setupMQTT() {

  String deviceID = "ESP8266Client-";
  deviceID += String(random(0xffff), HEX);

  Serial.println("Trying to connect to MQTT Broker.");
  if (MQTT.connect(deviceID.c_str())) {
    Serial.println("\nBroker connected!");
    MQTT.subscribe(inTopic);
  } else {
    Serial.println("Error. Trying again in 5 seconds.");
    delay(5000);
  }
}
