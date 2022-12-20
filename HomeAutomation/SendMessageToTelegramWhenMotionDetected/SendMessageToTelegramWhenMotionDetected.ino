#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


LiquidCrystal_I2C lcd (0x27, 16, 2);
const char* ssid = "legend hacker ✔";
const char* password = "123456789@fmn";


#define BOTtoken "5869156460:AAFaRyswvEhZpS7f6jLAaoCIp6vK67E9j8E"
#define CHAT_ID "5266762989"

#define Sensor D0
#define LEDR D3
#define LEDG D4
#define IR_SENSOR D7
#define Buzzer D5
#define MOTOR D2

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

  pinMode(Sensor, INPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(IR_SENSOR,INPUT);
  pinMode(MOTOR, OUTPUT);
  
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
void loop() {
  digitalWrite(MOTOR, HIGH);
  bool value = digitalRead(Sensor);
  Serial.println(value);
  if (value == 1) {
    Serial.println("Motion Detected");
    digitalWrite(LEDR, HIGH);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LEDG, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Motion Detected");
    bot.sendMessage(CHAT_ID, "Motion detected!!", "");
  } else if (value == 0) {
    digitalWrite(LEDR, LOW);
    digitalWrite(Buzzer, LOW);
    digitalWrite(LEDG, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("No Motion      ");
  }
  int sleep = digitalRead(IR_SENSOR);
  if(sleep == LOW){
    delay(2000);
    digitalWrite(Buzzer, HIGH);
    digitalWrite(MOTOR, LOW);
  }
  else{
    if(sleep == HIGH){
      digitalWrite(Buzzer, LOW);
      digitalWrite(MOTOR, HIGH);
    }
  }
}
