
int photocellPin = 0;
int ledPin = 11;
int buttonLeftPin = 4;
int buttonRightPin = 2;

int minLed = 0, maxLed = 255;
int minCell = 0, maxCell = 1023;

int photocellVal, ledVal, btnLVal, btnRVal;        

void setup(void) 
{
  pinMode(buttonLeftPin, INPUT);
  pinMode(buttonRightPin, INPUT);
}
 
void loop(void) 
{
  photocellVal = analogRead(photocellPin);
  btnLVal = digitalRead(buttonLeftPin);
  btnRVal = digitalRead(buttonRightPin);
 
  if (btnLVal == HIGH) {
    minCell = photocellVal;
    //maxCell = 1023;
  }
  if (btnRVal == HIGH) { 
    maxCell = photocellVal;
    //minCell = 0;
  }
  
  photocellVal = constrain(photocellVal, minCell, maxCell);
  photocellVal = maxCell - photocellVal + minCell;
  ledVal = map(photocellVal, minCell, maxCell, 0, 255);
  ledVal = constrain(ledVal, 0, 255);
  
  analogWrite(ledPin, ledVal);
  
  delay(10);
}

