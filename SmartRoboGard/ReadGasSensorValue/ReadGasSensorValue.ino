#define BUZZER_PIN 3
#define GAS_SENSOR A0
int sensorValue = 0;
int gas_detected_value = 330;

void alertSound()
{
  Serial.println("gas detected");
  analogWrite(BUZZER_PIN, 50);
  delay(100);
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
  sensorValue = analogRead(GAS_SENSOR);
  Serial.println(sensorValue);
  if (sensorValue > gas_detected_value)
  {
    sendAlert();
  }
} 
