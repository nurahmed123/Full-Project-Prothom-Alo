p;#include <Servo.h>

const int potentiometerPin = A0;   // Analog input pin for the potentiometer
const int servoPin = 9;            // Digital pin for the servo motor
const int servoPin1 = 8;            // Digital pin for the servo motor
                                                          
Servo servo;
Servo servo1;

void setup() {
  Serial.begin(9600);             // Initialize serial communication
  servo.attach(servoPin);         // Attaches the servo to the specified pin
  servo1.attach(servoPin1);         // Attaches the servo to the specified pin
}

void loop() {
  int potValue = analogRead(potentiometerPin);  // Read the potentiometer value
  int servoAngle = map(potValue, 0, 725, 0, 180);  // Map potentiometer value to servo angle range (0-180 degrees)
  
  servo.write(servoAngle);        // Set the servo position based on the potentiometer value
  servo1.write(servoAngle);        // Set the servo position based on the potentiometer value
  delay(15);                      // A small delay for smooth movement
  
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);       // Print the potentiometer value to the serial monitor
}
