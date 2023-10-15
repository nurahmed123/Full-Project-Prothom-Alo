// Motor driver connections
#define ENA_PIN 2   // Enable pin for motor A
#define IN1_PIN 3   // Input pin 1 for motor A
#define IN2_PIN 4   // Input pin 2 for motor A
#define ENB_PIN 5   // Enable pin for motor B
#define IN3_PIN 6   // Input pin 1 for motor B
#define IN4_PIN 7   // Input pin 2 for motor B


void setup() {
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  
  digitalWrite(ENA_PIN, HIGH);  // Enable motor A
  digitalWrite(ENB_PIN, HIGH);  // Enable motor B

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();

    if (input == '1') {
      // Clockwise
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, LOW);
      Serial.println("Motor running clockwise");
    } else if (input == '2') {
      // Counterclockwise
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
      digitalWrite(IN3_PIN, LOW);
      digitalWrite(IN4_PIN, HIGH);
      Serial.println("Motor running counterclockwise");
    } else if (input == '3') {
      // Turn left
      digitalWrite(IN1_PIN, LOW);
      digitalWrite(IN2_PIN, HIGH);
      digitalWrite(IN3_PIN, HIGH);
      digitalWrite(IN4_PIN, LOW);
      Serial.println("Motor turning left");
    } else if (input == '4') {
      // Turn right
      digitalWrite(IN1_PIN, HIGH);
      digitalWrite(IN2_PIN, LOW);
      digitalWrite(IN3_PIN, LOW);
      digitalWrite(IN4_PIN, HIGH);
      Serial.println("Motor turning right");
    }
  }
}