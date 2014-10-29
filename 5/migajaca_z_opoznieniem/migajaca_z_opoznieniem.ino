#define EPS 10
#define SIZE 100

short pinLed = 12;
short pinBtn = 2;
boolean queue[SIZE];

void setup(void)
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBtn, INPUT);
  for (int i = 0; i < SIZE; i++) 
    queue[i] = false;
}

short btnState;
short pos = 0;

void loop(void)
{
    digitalWrite(pinLed, queue[pos]?HIGH:LOW);
  
  btnState = digitalRead(pinBtn);
  queue[pos++] = btnState == HIGH;
  if (pos == SIZE) pos = 0;
  
  delay(EPS);
}
