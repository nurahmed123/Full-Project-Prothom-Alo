#include <SoftwareSerial.h>

SoftwareSerial SIM800L(3,2);//SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
SIM800L.begin(9600); // GSM Module Baud rate – communication speed
Serial.begin(9600); // Baud rate of Serial Monitor in the IDE app
Serial.println ("Text Messege Module Ready & Verified");
delay(100);
Serial.println ("Type s to send message or r to receive message");
}

void loop()
{
if (Serial.available()>0)
switch(Serial.read())
{
case 's':
SendMessage();
break;
case 'r':
RecieveMessage();
break;
case 'a':
Makecall();
break;
case 'b':
Receivingcall();
break;
}

if (SIM800L.available()>0)
Serial.write(SIM800L.read());
}

void SendMessage()
{
Serial.println ("Sending Message please wait….");
SIM800L.println("AT+CMGF=1"); //Text Mode initialisation
delay(1000);
Serial.println ("Set SMS Number");
SIM800L.println("AT+CMGS=\"+8801575056952\"\r"); // Receiver’s Mobile Number
delay(1000);
Serial.println ("Set SMS Content");
SIM800L.println("Please subscribe friendtechbd youtube channel ");// Messsage content
delay(100);
Serial.println ("Done");
SIM800L.println((char)26);// delay(1000);
Serial.println ("Message sent succesfully");
}

void RecieveMessage()
{
Serial.println ("Receiving Messeges");
delay (1000);
SIM800L.println("AT+CNMI=2,2,0,0,0"); // Eeceiving Mode Enabled
delay(1000);
Serial.write ("Messege Received Sucessfully");
}
void Makecall()
{
Serial.println ("Makeing calling");
delay (1000);
SIM800L.println("ATD+ +8801575056952;");
delay(1000);
Serial.write ("make call");
delay(20000); // wait for 20 seconds...
SIM800L.println("ATH"); //hang up
//updateSerial();

}

void Receivingcall()
{
Serial.println ("Receiving call");
delay (1000);
SIM800L.println("ATA"); // Eeceiving Mode Enabled
delay(1000);
Serial.write ("receive call Sucessfully");
}
