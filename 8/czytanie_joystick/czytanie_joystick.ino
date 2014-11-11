
/* Piny */
short pinX = 0;
short pinY = 1;
short leds[] = {8, 9, 10, 11}; // w dodatniej kolejnosci!

/* I/O */
short valX, valY;

/* Parametry gry */
const short acceptTime = 2000; //  czas (w ms) po upływie, którego nie przyznaje się punktów
const short roundDelayTime = 200;

short currentRound = 0; 
short ledNo;

unsigned int roundStartTime;
unsigned int gameStartTime;
unsigned int gameTime = 30000;
unsigned int time;
unsigned int pointsTotal = 0;

/* Debug */
String debugDirMap[] = {"+X", "+Y", "-X", "-Y"}; 


boolean isInRange(int val, int minVal, int maxVal) 
{
  return val >= minVal && val <= maxVal;
}

void initNewGame()
{
  int input = 0;
  Serial.println("Wcisnij s by rozpoczac nowa gre.");
  while (input != 's' && input != 'S') {
    if (Serial.available())
      input = Serial.read();
    delay(10);
  }

  input = 0;
  Serial.println("Czas gry (sekundy)?");
  while (input <= 0) {
    while (!Serial.available()) delay(10); // wait for input
    input = Serial.parseInt();
  }
  Serial.print("Nowa gra: ");
  Serial.println(input);
  gameTime = input * 1000;
  gameStartTime = millis();
}

void nextRound()
{
  // leds off & delay
  for (int i = 0; i < 4; i++)
    digitalWrite(leds[i], LOW);
  delay(roundDelayTime);
  
  ledNo = random(4);
  digitalWrite(leds[ledNo], HIGH);
  roundStartTime = millis();
  
  // debug
  // Serial.println(debugDirMap[ledNo]);
}

void setup() 
{
  Serial.begin(9600);
  randomSeed(analogRead(5));
  
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
  
  initNewGame();
  nextRound();
}

void loop() 
{
  valX = analogRead(pinX);
  valY = analogRead(pinY);
  time = millis();
  
  if ( 
      (ledNo == 0 && valX > 900 && isInRange(valY, 510, 530)) ||   // +x
      (ledNo == 1 && valY > 900 && isInRange(valX, 490, 510)) ||   // +y
      (ledNo == 2 && valX < 20  && isInRange(valY, 510, 530)) ||   // -x
      (ledNo == 3 && valY < 20  && isInRange(valX, 490, 510))      // -y
   ) {
    
    /* Oblicz punkty */
    unsigned int diff = time - roundStartTime;
    int points = acceptTime - diff;
    points = points > 0 ? points : 0;
    pointsTotal += points;
    
    Serial.println("Brawo!");
    Serial.print("Czekalem ");
    Serial.print(diff);
    Serial.print(" milisekund. Otrzymujesz ");
    Serial.print(points);
    Serial.println(" punktow.");
    Serial.print("Pozostalo sekund: ");
    Serial.println((gameTime - (time - gameStartTime)) / 1000);

    nextRound();
  }
    
  if (time - gameStartTime > gameTime) {
    Serial.println("Koniec gry!");
    Serial.print("Zdobyles(as) ");
    Serial.print(pointsTotal);
    Serial.println(" punktow.");
    
    digitalWrite(leds[ledNo], LOW);
    initNewGame();
    nextRound();
  }
}
