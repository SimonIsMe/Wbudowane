/*
short pinLed = 12;
short pinBtn = 2;

#define EPS 10
#define QUEUE_SIZE 256

long queue[QUEUE_SIZE];
short qStart = 0, qEnd = 0;

void meminit(long* array, long length, long val)
{
  long i = 0;
  while (i < length) 
    array[i++] = val; 
}

void setup(void)
{
  pinMode(pinLed, OUTPUT);
  pinMode(pinBtn, INPUT);
  meminit(queue, QUEUE_SIZE, -100);
}

short btnState, btnPrevState = LOW;
long currentTime;

void loop(void)
{
  btnState = digitalRead(pinBtn);
  currentTime = millis();
  
  if (abs(queue[qStart] - currentTime) < EPS) {  
    digitalWrite(pinLed, HIGH);
    if (++qStart == QUEUE_SIZE) qStart = 0;
  } else {
    digitalWrite(pinLed, LOW);
  }
    
  if (btnState == HIGH) {
    queue[qEnd++] = currentTime + 1000;
    if (qEnd == QUEUE_SIZE) qEnd = 0;
  }
  
  delay(EPS);
}
*/
