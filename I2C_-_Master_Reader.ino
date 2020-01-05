#include <Wire.h>

// DATA Variables
String GPSdata = "";
int potentiometervalue = 0;
byte TempMotor = 0;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  SerialUSB.begin(9600);  // start serial for output
}

void loop() {
  Master_writer();
  Master_reader();
  GPSdata = GPS_Module ();
}

void Master_reader ()
{
  potentiometervalue = 0;
  TempMotor = 0;
  int i =0;
  String completestring = "";
  Wire.requestFrom(8, 4);    // request 4 bytes from slave device #8
  while (Wire.available()) {// slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    completestring += c;
    switch (i)
    {
      case 0:
      potentiometervalue = c*256;
      break;
      
      case 1:
      potentiometervalue += c;
      break;
      
      case 3:
      TempMotor = c;
      break;
    }
    i++;
  }
  SerialUSB.print("potentiometervalue\t");
  SerialUSB.println(potentiometervalue);
  SerialUSB.print("TempMotor\t");
  SerialUSB.println(TempMotor);
  SerialUSB.println("");
  //Serial.println(completestring);         // print the character
  delay(500);
}

void Master_writer ()
{
   delay(50);
  SerialUSB.println("Write data to slave");
  
  // Write a charatre to the Slave
  Wire.beginTransmission(8);
  Wire.write("send data");
  Wire.endTransmission();
    
  SerialUSB.println("Receive data"); 
}

String GPS_Module ()
{
  String data = "";
    while (SerialUSB.available() > 0){
    // get the byte data from the GPS
    byte gpsData = Serial.read();
    data += gpsData;
    SerialUSB.println(gpsData);
    SerialUSB.println("");
  } 
  return data ;
}
