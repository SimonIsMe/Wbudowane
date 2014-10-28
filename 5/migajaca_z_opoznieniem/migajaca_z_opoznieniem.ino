int pin = 13;
int pinPast = 12;
volatile int state = LOW;

unsigned long currentTime;
String polecenia = "";

void setup()
{
  pinMode(pin, OUTPUT);
  pinMode(pinPast, OUTPUT);
  attachInterrupt(0, blink, CHANGE);

  Serial.begin(9600);
  Serial.print(currentTime);
}

void loop()
{
  digitalWrite(pin, state);
  currentTime = millis();  
  
  if (getPierwsze() != 0 && currentTime >= getPierwsze()) {
    if (digitalRead(pinPast) == HIGH) {
      digitalWrite(pinPast, LOW);
    } else {
      digitalWrite(pinPast, HIGH);
    }
    delPierwsze();
  }
}

void blink()
{
  unsigned long time = millis() + 1000;  
  polecenia = polecenia + time + ",";
  
  state = !state;
}

unsigned long getPierwsze()
{
  int dokad = polecenia.indexOf(',');
  String sCzas = polecenia.substring(0, dokad);
  
  unsigned long toReturn = 0;
  int pozycji = sCzas.length();
  for (int i = pozycji - 1; i >= 0; i--) {
    toReturn += parse(sCzas.substring(i, i + 1)) * pow(10, pozycji - i - 1);
  }
  
  return toReturn;
}

unsigned long parse(String cyfra)
{
  if (cyfra == "0")
      return 0;

  if (cyfra == "1")
    return 1;    
    
  if (cyfra == "2")
    return 2;    

  if (cyfra == "3")
    return 3;  
  if (cyfra == "0")
      return 0;

  if (cyfra == "4")
    return 4;    
    
  if (cyfra == "5")
    return 5;    

  if (cyfra == "6")
    return 6;  
    
  if (cyfra == "7")
      return 7;

  if (cyfra == "8")
    return 8;    
    
  if (cyfra == "9")
    return 9;
}

void delPierwsze()
{
  int dokad = polecenia.indexOf(',');
  polecenia = polecenia.substring(dokad + 1);
}

