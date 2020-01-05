int i , j = 0;

#include <Wire.h>
uint16_t count = 0;

void setup() {
  Serial.begin (9600);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event
  pinMode (A0, INPUT);
}

void loop() {
  delay(100);
}

void requestEvent()
{
  Serial.println("request recieved");
  int tosend = i + j/2;
  Wire.write( tosend ); // respond with message of 6 bytes
  Wire.write(",");
  Wire.write( j/2);             
 // Wire.write("this is the data");  
 i++;
 j++;        
}

void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
