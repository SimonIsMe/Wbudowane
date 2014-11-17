int pin[5] = {2,3,4,5,6};

bool state[5][5] = {
  {1,0,0,0,1},
  {0,1,0,1,0},
  {0,0,1,0,0},
  {0,1,0,1,0},
  {1,0,0,0,1}
};

int time = 50;
int currectState = 4;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pin[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin[i], state[currectState][i]);
  }
  
  delay(time);
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin[i], state[currectState][i]);
  }
  
  delay(time);
  
  currectState = (currectState + 1) % 5;
}
