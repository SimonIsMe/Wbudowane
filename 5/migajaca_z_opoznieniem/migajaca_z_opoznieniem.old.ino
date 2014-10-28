/*
int pin = 13;
int pinPast = 12;
int buttonPin = 2;
volatile int state = LOW;

unsigned long currentTime;
String polecenia = "";

void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(pinPast, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  Serial.print(currentTime);
}

void loop()
{
  
  currentTime = millis();  
  
  if (digitalRead(buttonPin) == HIGH) {    
     blink();
     delay(150);
  }
  
  if (getPierwsze() != 0 && currentTime >= getPierwsze()) {
    if (digitalRead(pinPast) == HIGH) {
      digitalWrite(pinPast, LOW);
       digitalWrite(pin, LOW);
    } else {
      digitalWrite(pinPast, HIGH);
       digitalWrite(pin, HIGH);
    }
   
    delPierwsze();
  }
}

void blink()
{
  unsigned long time = millis() + 1000;  
  polecenia = polecenia + time + ",";
  Serial.println(polecenia);
  
  state = !state;
}

unsigned long getPierwsze()
{
  int dokad = polecenia.indexOf(',');
  String sCzas = polecenia.substring(0, dokad);
  
  unsigned long toReturn = 0;
  int pozycji = sCzas.length();
  
  for (int i = 0; i < pozycji; i++) {
    toReturn *= 10;
    toReturn += (int)(sCzas[i] - '0');
  }
  
  return toReturn;
}

void delPierwsze()
{
  int dokad = polecenia.indexOf(',');
  polecenia = polecenia.substring(dokad + 1);
}
*/

