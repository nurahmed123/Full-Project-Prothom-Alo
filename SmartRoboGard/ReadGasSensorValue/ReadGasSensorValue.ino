
#define BUZZER_PIN 3

void alertSound()
{
  analogWrite(BUZZER_PIN, 50);
  delay(500);
  analogWrite(BUZZER_PIN, 0);    
}

void sendAlert()
{
  alertSound();
}

void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if (sensorValue > 200)
  {
    sendAlert();
  }
} 
