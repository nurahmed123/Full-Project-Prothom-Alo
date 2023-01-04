#include <Servo.h> //includes the servo library
Servo myservo;
Servo firstRailServo;
Servo secoundRailServo;

#define echopin 10 // echo pin
#define trigpin 9 // Trigger pin

const int servoPin = 7;
const int firstRailGetServo = 4;
const int secoundRailGetServo = 5;
const int firstIR = 2;
const int secoundIR = 3;
const int IRMatchingValue = LOW;
bool getOperation = true;
int trainDetection = LOW;
int trainCrossed = LOW;

int set_cm = 20;

long ultra_time;
long dis_cm;

void setup(){ // put your setup code here, to run once

  Serial.begin(9600);// initialize serial communication at 9600 bits per second:
  
  myservo.attach(servoPin);
  myservo.write(0);

  firstRailServo.attach(firstRailGetServo);
  secoundRailServo.attach(secoundRailGetServo);
  
  pinMode (trigpin, OUTPUT); // declare ultrasonic sensor Trigger pin as Output
  pinMode (echopin, INPUT);  // declare ultrasonic sensor Echo pin as input
  pinMode(secoundIR, INPUT);
  pinMode(firstIR, INPUT);

  firstRailServo.write(180);
  secoundRailServo.write(180);
  
  delay(1000); // Waiting for a while
}

void up(){
  myservo.write(20);
  delay(50);
  myservo.write(30);
  delay(50);
  myservo.write(40);
  delay(50);
  myservo.write(50);
  delay(50);
  myservo.write(80);
  delay(50);  
  myservo.write(110);
  delay(3000); 
}

void getOpen(){
  Serial.println("get open");
  firstRailServo.write(180);
  secoundRailServo.write(180);
}

void getClose(){
  Serial.println("get close");
  firstRailServo.write(0);
  secoundRailServo.write(0);
}

void down(){
  myservo.write(0);
}

void loop(){ 
  //*************************
  ultra_read();
  //*************************
  
  Serial.print("Dis :");Serial.println(dis_cm); 
  
  if(dis_cm<set_cm){
    up();
  }
  
  if(dis_cm>set_cm){
    down();
  }
  
  delay(100); 


  // ----------------- train section -------------
  
  trainDetection = digitalRead(firstIR);
  Serial.print("train enter: ");
  Serial.println(trainDetection);
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

//**********************ultra_read****************************
void ultra_read(){
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  ultra_time = pulseIn (echopin, HIGH);
  dis_cm =  ultra_time / 29 / 2; 
}
