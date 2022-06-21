#include <SoftwareSerial.h>

SoftwareSerial mySerial(16, 17); // RX, TX  //GPIO 16 & 17 pin of ESP32


void setup()
{
  Serial.begin(9600);    // opens up the communication port which is used to upload the program on arduino
  Serial.println("Goodnight moon!");   //if we press enable button on ESP32 we can see the printed message informing us about openning the serial port. it will be shown on the port where arduino usb is conneted


  mySerial.begin(9600);                // opens up the communication port which is connected through USB-TTL
  mySerial.println("Hello, world?");      //if we press enable button on ESP32 we can see the printed message informing us about openning the serial port
}

void loop() // run over and over
{
  if (mySerial.available()>0)           // if we transmit data through this port, data will be save in bytes number (like 1,2,3....)    (USB-TLL port)
    Serial.write(mySerial.read());       //after reading the data from USB-TTL port, this data will write into the serial monitor attached to the port(Arduino USB port)
  if (Serial.available()>0)                 // vice-versa
    mySerial.write(Serial.read());
}
