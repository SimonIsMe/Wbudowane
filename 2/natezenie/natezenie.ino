
int photocellPin = 0;
int ledPin = 11;
int buttonLeftPin = 4;
int buttonRightPin = 2;
int internalLedPin = 13;

int minLed = 0, maxLed = 255;
int minCell = 0, maxCell = 1023;

int photocellVal, ledVal, btnLVal, btnRVal;        

int counter = 0;

void setup(void) 
{
  pinMode(buttonLeftPin, INPUT);
  pinMode(buttonRightPin, INPUT);
  pinMode(internalLedPin, OUTPUT);
  Serial.begin(9600);
}
 
void loop(void) 
{

  photocellVal = analogRead(photocellPin);
  btnLVal = digitalRead(buttonLeftPin);
  btnRVal = digitalRead(buttonRightPin);
  
  counter++;
  if (counter % 100 == 0) {
    Serial.print(photocellVal);
    Serial.print(" => ");
    Serial.println(ledVal);
    counter = 0;
  } 
  
  if (btnLVal == HIGH) {
    Serial.println("L");
    minCell = photocellVal;
  //  maxCell = 1023;
  }
  if (btnRVal == HIGH) {
    Serial.println("R");    
    maxCell = photocellVal;
   // minCell = 0;
  }
  
  photocellVal = constrain(photocellVal, minCell, maxCell);
  photocellVal = maxCell - photocellVal + minCell;
  ledVal = map(photocellVal, minCell, maxCell, 0, 255);
  if (ledVal < 0) {
    ledVal = 0;
  }
  if (ledVal > 255) {
    ledVal = 255;
  }
  
  analogWrite(ledPin, ledVal);
  
  delay(10);
}

