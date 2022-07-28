#include <EEPROM.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#define EEPROM_SIZE 101                             //ESP32 max EEPROM size is 512 byte
#define REQUIRED_SIZE 99
// button is used for writing in memory when it is pressed.
uint16_t button = 5; 

//If the string is arduino String how to handle this?this code will explain this.
//look at comment which is numbered as #.
//String ESP32_ID = "id: 23";     //#
                                                                   
bool flag = true;    //this varible is used to print single time in serial monitor

/*
variable to store data;
*/
struct Registration {
  uint32_t ESP_REG_ID;
  uint16_t ESP_ID;
  uint8_t Factory_ID;
  uint8_t Plant_ID;
} espRegData;


/*
receives string argument, convert this string to hexadecimal value and return this value.
*/
uint32_t get_hex_string(string hexstring) {
  u_int32_t hex=0;
  std::stringstream str;
  str << std::hex << hexstring;
  str >> hex;
  return hex;
}

/*
store value to next location continuosly.. 
lastByteAddress remember the location by storing the value in the EEPROM 100 location.
*/
void storeValueToNextByte(string valueToBeStored) {
  uint16_t lastByteAddress = EEPROM.read(100);
  lastByteAddress++;
  EEPROM.write(100, lastByteAddress);
  EEPROM.write(lastByteAddress, get_hex_string(valueToBeStored));
  EEPROM.commit();

  if (lastByteAddress >= REQUIRED_SIZE) {
    lastByteAddress = 4;
    EEPROM.write(100, lastByteAddress);
  }
  
}

/*
  receive string argument and convert it to hex then store it in the EEPROM location 0,1,2,3.
  if the string is "12345678" then it stores "78" in location 0, "56" in location 1, "34" in location 2 and "12" in location 3.
*/
uint32_t store_hex_string_32bit(string hexstring) {
  if (hexstring.size() < 8 | hexstring.size() > 8) {
    return 0;
  }
  EEPROM.put(0, get_hex_string(hexstring));
  EEPROM.commit();
  EEPROM.write(100,4);
  return 0;
}

/*
it reads from memory location
*/
void read_hex_value_32bit() {
  espRegData.ESP_REG_ID = (EEPROM.read(3) << 24) | (EEPROM.read(2) << 16) | (EEPROM.read(1) << 8) | EEPROM.read(0);
  espRegData.Factory_ID = EEPROM.read(3);
  espRegData.Plant_ID = EEPROM.read(2);
  espRegData.ESP_ID = (EEPROM.read(1) << 8) | EEPROM.read(0);
}

/*
store value to specific memory location. remember you have to store 1 byte in the location.
*/
uint8_t storeValueToSpecificLocation(uint16_t SpecificByteAddress, string hexstring) {
  if (hexstring.size() > 2 | SpecificByteAddress > REQUIRED_SIZE) {
    return 0;
  }
  EEPROM.write(SpecificByteAddress, get_hex_string(hexstring));
  EEPROM.commit();
  return 0;
}

/*
store value to EEPROM location 0 and 1 for ESP32_ID. we can pass max 4 char otherwise it will not store the value in memory.
if string is "F3FA" then it store the F3FA hex value. if the string "F1B" then it stores 0F1B hex value.
*/
void store_hex_string_ESP32_ID_2Byte(string hexstring) {
  switch (hexstring.size())
  {
  case 4:
      EEPROM.write(0,get_hex_string(hexstring.substr(2,2)));
      EEPROM.write(1,get_hex_string(hexstring.substr(0,2)));
      EEPROM.commit();
    break;
  case 3:
      hexstring = "0"+ hexstring;
      EEPROM.write(0,get_hex_string(hexstring.substr(2,2)));
      EEPROM.write(1,get_hex_string(hexstring.substr(0,2)));
      EEPROM.commit();
    break;
  case 2:
      hexstring = "00"+ hexstring;
      EEPROM.write(0,get_hex_string(hexstring.substr(2,2)));
      EEPROM.write(1,get_hex_string(hexstring.substr(0,2)));
      EEPROM.commit();
    break;
  case 1:
    hexstring = "000"+ hexstring;
      EEPROM.write(0,get_hex_string(hexstring.substr(2,2)));
      EEPROM.write(1,get_hex_string(hexstring.substr(0,2)));
      EEPROM.commit();
  break;

    }
}

/*
store value to EEPROM location 3 for Factory_ID. we can pass max 2 char otherwise it will not store the value in memory.
if string is "FA" then it store the FA hex value. if the string "B" then it stores 0B hex value.
*/
void store_hex_string_FactoryID_1Byte(string hexstring) {
  switch (hexstring.size())
  {
  case 2:
   EEPROM.write(3,get_hex_string(hexstring));
   EEPROM.commit();
    break;
  case 1:
    hexstring = "0"+ hexstring;
   EEPROM.write(3,get_hex_string(hexstring));
   EEPROM.commit();
  break;
  }
}

/*
store value to EEPROM location 2 for Plant_ID. we can pass max 2 char otherwise it will not store the value in memory.
if string is "FA" then it store the FA hex value. if the string "B" then it stores 0B hex value.
*/
void store_hex_string_Plant_1Byte(string hexstring) {
  switch (hexstring.size())
  {
  case 2:
   EEPROM.write(2,get_hex_string(hexstring));
   EEPROM.commit();
    break;
  case 1:
    hexstring = "0"+ hexstring;
   EEPROM.write(2,get_hex_string(hexstring));
   EEPROM.commit();
  break;
  }
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  pinMode(button, INPUT);       //when button is pressed value will be stored in memory
}

void loop() {
    if(digitalRead(button)==HIGH){
      store_hex_string_32bit("11112222");
      store_hex_string_FactoryID_1Byte("34");
      store_hex_string_Plant_1Byte("56");
     //std::string x = ESP32_ID.c_str();                   //#
     //store_hex_string_ESP32_ID_2Byte(x.substr(3));       //#
     storeValueToSpecificLocation(40,"ee");
    }

      read_hex_value_32bit();
      storeValueToNextByte("AA");
    //  if(flag == true){
        Serial.print(espRegData.ESP_REG_ID, HEX);
        Serial.print("  ");
        Serial.print(espRegData.Factory_ID, HEX);
        Serial.print("  ");
        Serial.print(espRegData.Plant_ID, HEX);
        Serial.print("  ");
        Serial.print(espRegData.ESP_ID, HEX);
        Serial.print("    address: ");
        Serial.print(EEPROM.read(100),HEX);
        Serial.print("  ");
        Serial.print(EEPROM.read(EEPROM.read(100)),HEX);
        Serial.print("                ");
        Serial.println(EEPROM.read(40),HEX); 
       // flag = false;   
     // }
  delay(350);
}