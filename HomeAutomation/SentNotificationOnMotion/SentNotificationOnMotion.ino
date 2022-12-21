// IoT motion sensor by www.diyusthad.com
// www.youtube.com/c/diyusthad
// www.hackser.io/najad

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "legend hacker ✔"; //Your WiFI ssid
const char* password = "123456789@fmn"; //Your WiFi password
boolean PIRstate ; //variable to store PIR state
boolean lastPIRstate = HIGH;
int PIR = 0; //PIR connected to GPIO 0

WiFiClient wifiClient;

void setup () {

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  pinMode(PIR, INPUT); //digitalWrite(PIR, LOW);

  pinMode(2, OUTPUT);

  delay(30000);

}

void loop()
{

  PIRstate = digitalRead(PIR);  //HIGH when motion detected, else LOW

  if (PIRstate != lastPIRstate)  //Checking if there is any motion
  {

    digitalWrite(2, LOW);
    delay(100);
    digitalWrite(2, HIGH);
    if (WiFi.status() == WL_CONNECTED)  //Check WiFi connection status
    {
      HTTPClient http;  //Declare an object of class HTTPClient

      http.begin(wifiClient,"https://maker.ifttt.com/trigger/Motion_Detector_Project/json/with/key/lDvUwWO9_qFNU5Y4tDyL0P7h_5Yd_fHb9w3labZ5p3k");  //Specify request destination
      http.GET();   //Send the request
      http.end();   //Close connection

    }
    lastPIRstate = PIRstate;
  }

}
