void setup(){
  Serial.begin(9600);     // to communicate in UART between Sodaq and GPS
  SerialUSB.begin(9600);  // to print data on the serial monitor
}

void loop(){
  while (Serial.available() > 0){
    // get the byte data from the GPS
    byte gpsData = Serial.read();
    SerialUSB.write(gpsData);
  }
}
