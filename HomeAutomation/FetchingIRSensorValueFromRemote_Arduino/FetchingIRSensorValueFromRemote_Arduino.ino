//This Video Making by ElectriCircuit Subscribe this Channel
//https://www.youtube.com/channel/UCIr4PGxiEQWmYswJPueRlMQ
// Like this facebook Page: https://www.facebook.com/Electric-Circuit-108154251467438
// Follow In Instagram: https://www.instagram.com/electric_circuit_099/
// View Blog: https://electriccircuitarduino.blogspot.com/
#include <IRremote.h>

int IRpin = 12;
IRrecv irrecv(IRpin);
decode_results results;

void setup()  
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // Start the reciver

}

void loop() 
{
 if ( irrecv.decode(&results))
{
  Serial.println(results.value); //Print the sireal results value
  delay(100);
  irrecv.resume();
  }
}   



