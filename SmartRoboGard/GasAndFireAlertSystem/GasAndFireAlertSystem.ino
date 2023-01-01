#define SIGNAL_LIGHT 13
#define FLAMER_SENSOR 4
#define BUZZER_SENSOR 3
#define GAS_SENSOR A0
int gas_detected_value = 300;
int sensorValue = 0;
int FLAME = LOW;
String fireMassage = "Fire detected. Please take steps.";
String gasMassage = "Gas detected. Please take steps.";

//--------- main source ------------
void sendSMS(String message){
  Serial.println("Send message function is called");
  Serial.println(message);
}

void send_alert(String detection){
  Serial.println(detection);
  if(detection == "fire"){
    Serial.println("Fire detected");
    sendSMS(fireMassage);
  }
  else if(detection == "gas"){
    Serial.println("Gas detected");
    sendSMS(gasMassage);
  }
  
  digitalWrite(SIGNAL_LIGHT, HIGH); 
  
  digitalWrite(BUZZER_SENSOR, HIGH);
  delay(100);
  digitalWrite(BUZZER_SENSOR, LOW);
}

void clean_enviroment(){
  digitalWrite(BUZZER_SENSOR, LOW);
  digitalWrite(SIGNAL_LIGHT, LOW);
}


//--------- main source ------------
void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_SENSOR, OUTPUT);
  pinMode(FLAMER_SENSOR, INPUT);
  pinMode(SIGNAL_LIGHT, OUTPUT);
}

void loop(){
  FLAME = digitalRead(FLAMER_SENSOR);
  sensorValue = analogRead(GAS_SENSOR);
  Serial.println(sensorValue);
  
  if(FLAME == LOW){
    send_alert("fire");
  }
  else if(sensorValue > gas_detected_value)
  {
    send_alert("gas");
  }
  else{
    clean_enviroment();
  }
}
