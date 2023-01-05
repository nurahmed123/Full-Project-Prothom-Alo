#include <Servo.h>   //servo library

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;
int servoPin = 5;
int val;

// defines variables
long duration;
int distance;
int safetyDistance;

Servo myservo;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
pinMode(buzzer, OUTPUT);
pinMode(ledPin, OUTPUT);
Serial.begin(9600); // Starts the serial communication
myservo.attach(servoPin);
}

void down(){
//  Serial.println("down function is called");
//  myservo.write(0);
}

void up(){
//  Serial.println("up function is called");
//  myservo.write(180);
}


void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

safetyDistance = distance;
if (safetyDistance <= 15){
  up();
}
else{
  down();
}

val = Serial.parseInt();
if(val > 0){
  
  myservo.write(val);
}


// Prints the distance on the Serial Monitor
//Serial.print("Distance: ");
//Serial.println(distance);
}
