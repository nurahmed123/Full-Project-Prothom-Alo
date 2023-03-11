#include <Servo.h>
Servo test;
int i,j ;
const int anlog = 9;

void setup(){
  test.attach(5);
  Serial.begin(9600);
  test.write(0);
  pinMode(anlog, INPUT);
}

void loop(){
  int val = analogRead(anlog);
  test.write(val);
}
