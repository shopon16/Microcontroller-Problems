#include <Arduino.h>
#include <LiquidCrystal.h>

const int rs=14, rw=13, enable=19, d0=18, d1=5, d2=17, d3=16, d4=23, d5=22, d6=15, d7=21;
LiquidCrystal lcd(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   pinMode(rs, OUTPUT);
   pinMode(rw, OUTPUT);
   //pinMode(35, OUTPUT);
   pinMode(d0, OUTPUT);
   pinMode(d1, OUTPUT);
   pinMode(d2, OUTPUT);
   pinMode(d3, OUTPUT);
   pinMode(d4, OUTPUT);
   pinMode(d5, OUTPUT);
   pinMode(d6, OUTPUT);
   pinMode(d7, OUTPUT);
 lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("hello");
     digitalWrite(rs,LOW);
     digitalWrite(rw,LOW);
    // digitalWrite(35,LOW);
    digitalWrite(d0,LOW);        //D0
    digitalWrite(d1,HIGH);       //D1         
    digitalWrite(d2,HIGH);      //D2       high means open display low means shut display
    digitalWrite(d3,LOW);         //D3
    digitalWrite(d4,LOW);          //D4
    digitalWrite(d5,LOW);      //D5
    digitalWrite(d6,LOW);     //D6
    digitalWrite(d7,LOW);   //D7
    delay(1000);
}
