#include <WiFi.h>
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
  WiFi.begin("legend hacker", "123456789@fmn");
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to WiFi");
 
  Serial.print("Static IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.print("Listening on port: ");
  Serial.println(server.port());
}
 
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
    // handle incoming connections
  }
 
  // do other stuff
}
