int pinX = 0;
int pinY = 1;

int acceptedTime = 2000; //  czas (w ms) po upłuwie, którego nie przyznaje się punktów

int ledNo;
unsigned int timeForPlay = 10;
unsigned int timeStartGame;
unsigned int timeStart;
unsigned int time;

int pointsTotal = 0;

int valX, valY;


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(5));
  timeStartGame = millis();
  
  randomLedNo();
}

void loop() {
  valX = analogRead(pinX);
  valY = analogRead(pinY);
  
  if (
      (ledNo == 0 && valX < 20 && isInRange(valY, 490, 510)) ||
      (ledNo == 1 && valX > 900 && isInRange(valY, 490, 510)) ||
      (ledNo == 2 && valY > 900 && isInRange(valX, 510, 530)) ||
      (ledNo == 3 && valY < 20 && isInRange(valX, 510, 530))
   ) {
    Serial.println("Brawo!");
    time = millis();
    unsigned int diff = time - timeStart;
    int points = acceptedTime - diff;
    if (points < 0) {
      points = 0;
    }
    pointsTotal += points;
    Serial.print("Czekalem ");
    Serial.print(diff);
    Serial.print(" milisekund. Otrzymujesz ");
    Serial.print(points);
    Serial.println(" punktow. \n");
    randomLedNo();
  }
  
  
  if (timeStartGame + timeForPlay * 1000 < millis()) {
    /*Serial.println("Koniec gry!");
    Serial.print("Zdobyles(las) ");*/
    Serial.print(pointsTotal);
    Serial.println(" punktow.");
    ledNo = -1;
  }
  
}

void randomLedNo()
{
  timeStart = millis();
  ledNo = random(4);
  Serial.print("Wylosowalem ");
  Serial.println(ledNo);
}

boolean isInRange(int val, int minVal, int maxVal) {
  return val >= minVal && val <= maxVal;
}
