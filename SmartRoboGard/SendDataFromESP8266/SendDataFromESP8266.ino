#include <ESP8266WiFi.h>
 
const char* ssid = "legend hacker"; // replace with your WiFi network name
const char* password = "123456789@fmn"; // replace with your WiFi network password
 
IPAddress remote_ip(192, 168, 1, 100); // replace with the static IP address of your ESP32
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to WiFi");
}
 
void loop() {
  WiFiClient client;
 
  if (client.connect(remote_ip, 80)) { // replace 80 with the port number your ESP32 is listening on
    Serial.println("Connected to ESP32");
 
    String message = "Hello, ESP32!";
    client.print(message);
 
    Serial.println("Message sent to ESP32");
 
    client.stop();
  }
 
  delay(5000);
}
