
int pinHall = 0;
int pinBuzz = 10;
int pinLed  = 4;
int destVal = 0;

void setup(void) 
{
  Serial.begin(9600);
  
  pinMode(pinHall, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzz, OUTPUT);
  
  randomSeed(analogRead(4));
  destVal = (int)random(1024);
}

void beep(int signalTime, int waitingTime, int toneLevel)
{
  analogWrite(pinBuzz, toneLevel);
  delay(signalTime);
  analogWrite(pinBuzz, 0);
  delay(waitingTime);
}

int rd, dist;
int wait = 1000;
int led = LOW;

void loop(void)
{
  rd = analogRead(pinHall);
  
  Serial.print(destVal); Serial.print(" ");
  Serial.println(rd);
  
  dist = abs(destVal - rd);
  if (dist < 100) {
    led = HIGH;
    wait = 0; 
  } else {
    led = LOW;
    wait = floor(dist / 100.0 * 150.0);
  }
  
  digitalWrite(pinLed, led);
  beep(50, wait, 30);  
}
