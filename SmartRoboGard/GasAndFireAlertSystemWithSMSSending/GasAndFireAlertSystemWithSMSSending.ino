#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


LiquidCrystal_I2C lcd (0x27, 16, 2);
const char* ssid = "legend hacker ✔";
const char* password = "123456789@fmn";


#define BOTtoken "5921188279:AAFJh0V53tPxDi68_1vl8EnaX5IoT_LNhCQ"
#define CHAT_ID "5266762989"

#define FireSensor D7
#define GasSensor A0
#define Buzzer D0
#define LEDR D3
#define LEDG D4

int FireDetection = LOW;
int GasDetection = 0;
int gas_detected_value = 20;
String fireMassage = "Fire detected. Please take steps.";
String gasMassage = "Gas detected. Please take steps.";

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Wire.begin(D2, D1);
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org

  pinMode(FireSensor, INPUT);
  pinMode(GasSensor,INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.setCursor(a, 0);
    lcd.print(".");
    delay(500);
    a++;
  }

  Serial.println("");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  Serial.println(WiFi.localIP());
  delay(500);

  bot.sendMessage(CHAT_ID, "System started", "");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System started");
  delay(1000);
  lcd.clear();
}

void clean_enviroment(){
  digitalWrite(Buzzer, LOW);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Enviroment is clean now.");
}

void sendSMS(String message){
  Serial.println("your message is on the way to sent your phone ---> ");
  Serial.println(message);
  bot.sendMessage(CHAT_ID, message, "");
}

void send_alert(String detection){
  Serial.println("current detection is ---> ");
  Serial.println(detection);
  digitalWrite(Buzzer, HIGH);
  
  if(detection == "fire"){
    Serial.println("Fire detected");
    sendSMS(fireMassage);

    //Showing the current state to the display.
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Fire detected!!!");
  }
  else if(detection == "gas"){
    Serial.println("Gas detected");
    sendSMS(gasMassage);
    
    //Showing the current state to the display.
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Gas detected!!!");
  }
  digitalWrite(Buzzer, LOW);
}

void loop() {
  FireDetection = digitalRead(FireSensor);
  GasDetection = map(analogRead(GasSensor), 0, 1024, 0, 100);
  Serial.print("gas sensor value: ");
  Serial.println(GasDetection);
//  Serial.println("fire sensor value: ");
//  Serial.println(FireDetection);
  if (FireDetection == LOW) {
    send_alert("fire");
  } 
  else if (GasDetection > gas_detected_value) {
    send_alert("gas");
  }
  else{
    clean_enviroment();
  }
}
