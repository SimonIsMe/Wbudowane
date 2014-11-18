#include "PCM.h"

int czujnik = 0;
int swiatlo = 0;
 
void setup()
{
  
  pinMode(czujnik, INPUT);
  Serial.begin(9600);
}
 
void loop()
{
  swiatlo = analogRead(czujnik);
  
  if (swiatlo < 100) {
    Serial.println(swiatlo);
    startPlayback();
    delay(1000);
  }
  delay(10);
}

