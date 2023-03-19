#include <WiFi.h>
 
const char* ssid = "legend hacker"; // replace with your WiFi network name
const char* password = "123456789@fmn"; // replace with your WiFi network password
 
WiFiServer server(80); // replace 80 with the port number you want to listen on
 
void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to WiFi");
 
  server.begin();
  Serial.println("Server started");
}
 
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
    Serial.println("Client connected");
 
    while (client.connected()) {
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println(data);
      }
    }
 
    Serial.println("Client disconnected");
  }
 
  delay(1000);
}
