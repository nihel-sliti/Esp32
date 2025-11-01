#include <WiFi.h>
#include <PubSubClient.h>

// --- WiFi (Wokwi) ---
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";

// --- MQTT ---
const char* MQTT_HOST = "test.mosquitto.org";
const int   MQTT_PORT = ;// put ur port
const char* TOPIC_PUB = ""; // <- put your topic

WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) { delay(250); }
}

void connectMqtt() {
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  while (!mqtt.connected()) {
    String cid = "esp32-" + String((uint32_t)esp_random(), HEX);
    mqtt.connect(cid.c_str());             // sans user/pass
    if (!mqtt.connected()) delay(1000);    // retry
  }
}

void setup() {
  Serial.begin(9600);
  connectWifi();
  connectMqtt();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWifi();
  if (!mqtt.connected()) connectMqtt();
  mqtt.loop();

  static unsigned long last = 0;
  if (millis() - last > 3000) {            // toutes les 3s
    const char* msg = "hello from esp32";
    mqtt.publish(TOPIC_PUB, msg);
    Serial.println(String("PUB -> ") + TOPIC_PUB + " : " + msg);
    last = millis();
  }
}
