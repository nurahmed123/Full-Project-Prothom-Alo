#include <Servo.h>   //servo library

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 11;
const int ledPin = 13;
const int servoPin = 7;
const int firstRailGetServo = 4;
const int secoundRailGetServo = 5;
const int firstIR = 2;
const int secoundIR = 3;
const int IRMatchingValue = LOW;
bool getOperation = true;
int trainDetection = LOW;
int trainCrossed = LOW;


// defines variables
long duration;
int distance;
int safetyDistance;

Servo myservo;
Servo firstRailServo;
Servo secoundRailServo;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(secoundIR, INPUT);
  pinMode(firstIR, INPUT);
  Serial.begin(9600); // Starts the serial communication
  myservo.attach(servoPin);
  firstRailServo.attach(firstRailGetServo);
  secoundRailServo.attach(secoundRailGetServo);
  
  firstRailServo.write(180);
  secoundRailServo.write(180);
}

void getOpen(){
//  Serial.println("get open");
  firstRailServo.write(180);
  secoundRailServo.write(180);
}

void getClose(){
//  Serial.println("get close");
  firstRailServo.write(0);
  secoundRailServo.write(0);
}

void down(){
//  Serial.println("down function is called");
  myservo.write(0);
}

void up(){
//  Serial.println("up function is called");
  myservo.write(180);
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
  if (safetyDistance <= 10){
    up();
  }
  else{
    down();
  }
  
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(distance);
  
  trainDetection = digitalRead(firstIR);
//  Serial.print("train enter: ");
//  Serial.println(trainDetection);
  trainCrossed = digitalRead(secoundIR);
  Serial.print("train gone: ");
  Serial.println(trainCrossed);
  if (trainDetection == IRMatchingValue){
    getOperation = false;
  }
  if (trainCrossed == IRMatchingValue){
    getOperation = true;
  }
  
  if (getOperation){
    getOpen();
  }else{
    getClose();
  }
}
