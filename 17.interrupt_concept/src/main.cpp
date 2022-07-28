#include <Arduino.h>
int LED_PIN = 16;
int push_Button = 5;
int count = 0;

void IRAM_ATTR Ext_INT1_ISR()
{
  for (int i = 0; i <= 10; i++)
  {
    Serial.println(i);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200 );
  pinMode(LED_PIN,OUTPUT);
  pinMode(push_Button,INPUT);

  attachInterrupt(push_Button, Ext_INT1_ISR, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  count++;
  Serial.print("loop execution: ");
  Serial.println(count);
  delay(250);
}
