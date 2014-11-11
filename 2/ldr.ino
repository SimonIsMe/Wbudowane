
/* Pins */
int pinLdr = 0;
int pinLed = 11;
int pinMin = 4;
int pinMax = 2;

int lightMin = 0; 
int lightMax = 1023;

int ldr, invertedLdr, led;

void setup(void)
{
  pinMode(pinLdr, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinMin, INPUT);
  pinMode(pinMax, INPUT);
}

void loop(void)
{
  ldr = analogRead(pinLdr);
  
  if (digitalRead(pinMin) == HIGH)
    lightMax = ldr; // reversed!
  if (digitalRead(pinMax) == HIGH)
    lightMin = ldr;  
  
  ldr = constrain(ldr, lightMin, lightMax);
  invertedLdr = lightMax - ldr + lightMin;
  led = map(invertedLdr, lightMin, lightMax, 0, 255);
  analogWrite(pinLed, led);
}
