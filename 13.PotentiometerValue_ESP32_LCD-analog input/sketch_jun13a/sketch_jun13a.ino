
// include the library code:
#include <LiquidCrystal.h>
int registorValue = 0;
int i=-1;
int PotValue[1024];
int analog_value_read(){
  registorValue = analogRead(14);    //GPIO 14 is input.
  return registorValue;
}
void store_value_on_array(){
    i++;
  if(i<1025){
      PotValue[i] = registorValue;
      Serial.println(PotValue[i]);
    }
  else{
      i=-1;
    }
}

 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(19,22, 23, 18, 17, 16, 15);    //GPIO pin intialize. Dont select GPIO6-11 for I/O
 
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
    pinMode(14, INPUT);
      analogReadResolution(12);   //12bit resoluton count upto 2^12
  lcd.print("Voltage:");
}
 
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);            //this line move the cursor in row 1, coloumn 0
  // print the number of seconds since reset:
    analog_value_read();
  store_value_on_array();
    lcd.print(PotValue[i]);
    //Serial.println(PotValue[i]);
  delay(100);

}
