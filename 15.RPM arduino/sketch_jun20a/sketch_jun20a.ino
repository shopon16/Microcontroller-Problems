int count=0;
int void setup() {
  // put your setup code here, to run once:
pinMode(36,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(digitalRead(36)==LOW){
    count++;
    Serial.println(count);
  }
}
