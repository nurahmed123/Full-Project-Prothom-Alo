char BlueToothValue;
// TODO: Movement
// Motor A
int motor1Input1 = D0;
int motor1Input2 = D5;

// Motor B
int motor2Input1 = D3;
int motor2Input2 = D4;
int Speed = 255;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(motor1Input1, OUTPUT);
  pinMode(motor1Input2, OUTPUT);
  pinMode(motor2Input1, OUTPUT);
  pinMode(motor2Input2, OUTPUT);

}



// action
void left()
{
  Serial.println("l");
  // Initialize left motor to stop
  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, LOW);

  // Initialize right motor to move clockwise
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
  //analogWrite(motor2EnablePin, Speed);
}

void right(){
  Serial.println("r");
  
  // Initialize left motor to move clockwise
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  //analogWrite(motor1EnablePin, Speed);

  // Initialize right motor to stop
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, LOW);

} 
void backward(){
  Serial.println("b");

  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, HIGH);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, HIGH);
}
void forward(){
  Serial.println("f");

  // Initialize motors to move clockwise
  digitalWrite(motor1Input1, HIGH);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, HIGH);
  digitalWrite(motor2Input2, LOW);
}

void stop(){
  Serial.println("s");

  digitalWrite(motor1Input1, LOW);
  digitalWrite(motor1Input2, LOW);
  digitalWrite(motor2Input1, LOW);
  digitalWrite(motor2Input2, LOW);
}

//TODO: read bluetooth
void read_bluetooth(){
  if (Serial.available()) {
    BlueToothValue = Serial.read();
    // Serial.println(BlueToothValue);
  }

  if(BlueToothValue == 'L'){
      // Serial.println("l");
      left();
    }else if (BlueToothValue == 'R') {
      // Serial.println("r");
      right();
    }else if (BlueToothValue == 'F') {
      // Serial.println("f");
      forward();
    }else if (BlueToothValue == 'B') {
      // Serial.println("b");
      backward();
    }else if (BlueToothValue == 'S') {
      // Serial.println("s");
      stop();
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  read_bluetooth();
}
