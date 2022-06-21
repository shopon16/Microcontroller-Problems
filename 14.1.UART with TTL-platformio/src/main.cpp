#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(16, 17); // RX, TX  //GPIO 16 & 17 pin of ESP32       // opens up the communication port which is connected through USB-TTL

void setup()
{
/*
Serial.begin(speed, config)
speed: in bits per second (baud). Allowed data types: long.
config: sets data, parity, and stop bits. Valid values are:
SERIAL_5N1
SERIAL_6N1
SERIAL_7N1
SERIAL_8N1 (the default)
SERIAL_5N2
SERIAL_6N2
SERIAL_7N2
SERIAL_8N2
SERIAL_5E1: even parity
SERIAL_6E1
SERIAL_7E1
SERIAL_8E1
SERIAL_5E2
SERIAL_6E2
SERIAL_7E2
SERIAL_8E2
SERIAL_5O1: odd parity
SERIAL_6O1
SERIAL_7O1
SERIAL_8O1
SERIAL_5O2
SERIAL_6O2
SERIAL_7O2
SERIAL_8O2
*/

	mySerial.begin(9600,SWSERIAL_8E1);                     // data length 5, even parity, stop bit length 1, even parity check   
  mySerial.println("Hello, world?");         //if we press enable button on ESP32 we can see the printed message informing us about openning the serial port. it will be shown on the port where USB-TTL is connected
}
/////////

void loop() // run over and over
{
  if (mySerial.available()>0)  // if we transmit data through this port, data will be save in bytes number (like 1,2,3....)
    mySerial.write(mySerial.read());   //after reading the data, this statement will show the write the data to serial monitor attached to the port
}