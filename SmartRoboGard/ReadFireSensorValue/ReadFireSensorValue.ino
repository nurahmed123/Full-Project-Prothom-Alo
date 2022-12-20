int flamersensor = 8;
int buzzer = 3;
int signalLight = 13;
int flame = LOW;

int fire_detected(){
	Serial.println("Fire detected");
	digitalWrite(signalLight, HIGH);
	digitalWrite(buzzer, HIGH);
	delay(100);
	digitalWrite(buzzer, LOW);
}

int no_fire(){
	digitalWrite(buzzer, LOW);
	digitalWrite(signalLight, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(flamersensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(signalLight, OUTPUT);
}

void loop(){
	flame = digitalRead(flamersensor);
	
	if(flame == LOW){
		fire_detected();
	}
	else{
		no_fire();
	}
}
