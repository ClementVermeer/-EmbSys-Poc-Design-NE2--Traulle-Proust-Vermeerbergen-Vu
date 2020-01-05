#define CAYENNE_PRINT SerialUSB  // Comment this out to disable prints and save space
#include <CayenneLPP.h>
#include <Wire.h> // For I2C communication between MCU and VCU
#define GPS_Module Serial  // UART communication between GPS module and Sodaq explorer

// DATA Variables
String GPSdata = "";
int potentiometervalue = 0;
byte TempMotor = 0;

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "81e9c3e0-2043-11ea-b301-fd142d6c1e6c";
char password[] = "39d825c7ad0a993b7611442ae6595b06a615f818";
char clientID[] = "219b42f0-204f-11ea-8221-599f77add412";

void setup() {
  Wire.begin(); 
  SerialUSB.begin(9600);
  Serial2.begin(9600);
  Cayenne.begin(username, password, clientID);
}

void loop() {
  Cayenne.loop();
  Master_writer();
  Master_reader();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Add fields to the Cayenne interface :  template <typename T> uint8_t CayenneLPP::addField(uint8_t type, uint8_t channel, T value) 
  Cayenne.virtualWrite(0, millis());
  GPSdata = GPS_Module ();
  Cayenne.addField("GPS data", 1, GPS_Module ();
  Cayenne.addField("temperature data", 2,potentiometer );
  Cayenne.addField("potentiometer data", 3, TempMotor);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

void Master_reader ()
{
  potentimeter = 0;
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
      potentiometer = c*64;
      break;
      
      case 1:
      potentiometer += c;
      break;
      
      case 3:
      TempMotor = c;
      break;
    }
    i++;
  }
  SerialUSB.println(completestring);         // print the character
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
    while (Serial.available() > 0){
    // get the byte data from the GPS
    byte gpsData = Serial.read();
    data += gpsdata;
    SerialUSB.write(gpsData);
  } 
  return data 
}
