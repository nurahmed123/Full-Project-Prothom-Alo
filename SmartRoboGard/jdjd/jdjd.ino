#include <SoftwareSerial.h>

SoftwareSerial SIM900A(D5, D6); // gsm module connected here

#define FireSensor D7
#define GasSensor A0
#define Buzzer D0

int FireDetection = LOW;
int GasDetection = 0;
int gas_detected_value = 20;
String fireMassage = "Fire detected. Please take steps.";
String gasMassage = "Gas detected. Please take steps.";

void setup() {
  Serial.begin(9600);
  SIM900A.begin(9600);

  pinMode(FireSensor, INPUT);
  pinMode(GasSensor,INPUT);
  pinMode(Buzzer, OUTPUT);
  
}

void clean_enviroment(){
  digitalWrite(Buzzer, LOW);
}

void sendSMS(String message){
  Serial.println ("Sending Message please wait….");
  SIM900A.println("AT+CMGF=1"); //Text Mode initialisation
  delay(1000);
  Serial.println ("Set SMS Number");
  SIM900A.println("AT+CMGS=\"+8801886772094\"\r"); // Receiver’s Mobile Number
  delay(1000);
  Serial.println ("Set SMS Content");
  SIM900A.println(message);// Messsage content
  delay(100);
  Serial.println ("Done");
  SIM900A.println((char)26);// delay(1000);
  Serial.println ("Message sent succesfully");
}

void send_alert(String detection){
  Serial.print("current detection is ---> ");
  Serial.println(detection);
  analogWrite(Buzzer, 200);
  
  if(detection == "fire"){
    Serial.println("Fire detected");
    sendSMS(fireMassage);
  }
  else if(detection == "gas"){
    Serial.println("Gas detected");
    sendSMS(gasMassage);
  }
  digitalWrite(Buzzer, LOW);
}

void loop() {
  FireDetection = digitalRead(FireSensor);
  GasDetection = map(analogRead(GasSensor), 0, 1024, 0, 100);
  Serial.print("gas sensor value: ");
  Serial.println(GasDetection);
  if (FireDetection == LOW) {
    send_alert("fire");
  } 
  else if (GasDetection > gas_detected_value) {
    send_alert("gas");
    delay(3000);
  }
  else{
    clean_enviroment();
  }
}