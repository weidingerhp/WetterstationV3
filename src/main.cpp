#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

// Replace with your network credentials
const char* ssid = "XXX";
const char* password = "XXX";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// BME280 connect to ESP32 I2C (GPIO 21 = SDA, GPIO 22 = SCL)
// BME280 connect to ESP8266 I2C (GPIO 4 = SDA, GPIO 5 = SCL)
Adafruit_BME280 bme;      

void setup() {
  Serial.begin(115200);

  // Init BME280 sensor
  // if (!bme.begin(0x76)) {
  //   Serial.println("Could not find a valid BME280 sensor, check wiring!");
  //   while (1);
  // }
  
  // Connect to Wi-Fi
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  SPIFFS.begin();

  server.addHandler(&ws);
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
}

long old_millis;

bool timeIsUp() {
  if(millis() > old_millis + 5000) {
    old_millis = millis();
    return true;
  }
  return false;
}

void loop() {
  if(timeIsUp()) {

    ws.textAll("{\"temperatur\": 10, \"luftfeuchte\": 55}");
  }
  // put your main code here, to run repeatedly:

}
