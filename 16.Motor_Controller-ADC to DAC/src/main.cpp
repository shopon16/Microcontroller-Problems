#include <Arduino.h>
#include <main.h>

int pwm_output_pin = 32;     //connected to the enable pin of the motor controller which is pwm pin
int dir_in1 = 18;            // motor direction pin
int dir_in2 = 5;             // motor direction pin
int potpin = 39;             // analog voltage from Potentiometer

void setup() {

  pinMode(pwm_output_pin, OUTPUT);
  pinMode(potpin, INPUT);
  pinMode(dir_in1, OUTPUT);
  pinMode(dir_in2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(dir_in1, HIGH);
  digitalWrite(dir_in2, LOW);

  int potValue = analogRead(potpin);                // Read potentiometer value
  int pwmOutput = map(potValue, 0, 4095, 0 , 255);  // Map the potentiometer value from 0 to 255        //DAC is 8 bit
  analogWrite(pwm_output_pin, pwmOutput);           // Send PWM signal to L298N Enable pin
  
  Serial.println(pwmOutput);
}