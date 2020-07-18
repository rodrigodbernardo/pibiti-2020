class Nodemcu {
  public:
    void setupWiFi(ESP8266WiFiMulti wifiMulti);
    void setupOTA();
    void setupMQTT(PubSubClient MQTT);
    void inputMQTT(char* topic, byte* payload, unsigned int length);
  private:
    const char* SSID_01 = "FLAVIO_02";
    const char* PASS_01 = "8861854611";
};
