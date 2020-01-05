#include <Wire.h>

//FOR POTENTIOMETER
const int potentiometerpin = A0;
int potentiometervalue = 0;

//FOR TEMP :
#define TempMotorPin A1
byte TempMotor = 0;

void setup() 
{
  //FOR POTENTIOMETER
  Serial.begin (9600);
  pinMode (potentiometerpin, INPUT);

  //FOR TEMERATURES
  pinMode (TempMotorPin, INPUT);

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); // register event
}

void loop() 
{
  //POTENTIOMETER
  potentiometervalue = analogRead (potentiometerpin);
  Serial.print ("potentiometer value ");
  Serial.println(potentiometervalue);

  // TEMPERATURES
  TempMotor = ReadTemperature (TempMotorPin);
  //Serial.println(analogRead(A3));
  Serial.print("temperature value ");
  Serial.println(TempMotor);
  Serial.println ("");
  
  delay(1000);
}

byte ReadTemperature(int pin)
{
  // Serial.println ( analogRead (pin));
  float reading = 5 * analogRead (pin);
  float voltage = reading / 1023;
  byte temperature = (voltage - 0.55 )*100;
  return temperature;
}

void requestEvent()
{
  Serial.println("request recieved");
  Wire.write( potentiometervalue>>8); 
  Wire.write( potentiometervalue<<8); 
  Wire.write(",");
  Wire.write( TempMotor);             
 // Wire.write("this is the data");  
       
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
