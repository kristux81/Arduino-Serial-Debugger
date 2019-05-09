#include "SerialDebugger.h"

void setup() {
   Serial.begin(9600);

   for(int i=22; i<=32; i++){
      pinMode(i, INPUT);
   }
   
   for(int i=33; i<=52; i++){
      pinMode(i, OUTPUT);
   }

   for(int i=33; i<=52; i+=2){
      digitalWrite(i, HIGH);
   }
}

unsigned int i=0;
void loop() {
  serialDebugger();
  Serial.print("This is a sample console msg : ");
  Serial.println(i++);
  if(i>=65530) i=0;
  delay(1000);
}
