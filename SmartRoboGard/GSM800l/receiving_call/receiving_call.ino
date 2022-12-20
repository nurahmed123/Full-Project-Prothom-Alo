#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial mySerial(3, 2); //SIM900 Tx & Rx is connected to Arduino #7 & #8

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM900
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
}

void loop()
{
Serial.println ("Receiving call");
delay (1000);
mySerial.println("ATA"); // Eeceiving Mode Enabled
delay(1000);
Serial.write ("receive call Sucessfully");


}
