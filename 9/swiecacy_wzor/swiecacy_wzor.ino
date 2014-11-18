int pin[5] = {2,3,4,5,6};
int pinBuzzer = 10;

int stateNo = 14;
bool state[14][5] = {
  
  {0,0,0,0,0},


  //  litera "K"
  {1,0,0,0,1},
  {0,1,0,1,0},
  {0,0,1,0,0},  
  {1,1,1,1,1},
  {0,0,0,0,0},
  
  //  spacja
  {0,0,0,0,0},
  {0,0,0,0,0}, 
  {0,0,0,0,0},
  
  //  litera "O"  
  {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
  
  {0,0,0,0,0}
};
/*
bool state[17][5] = {
  
  {0,0,0,0,0},

  //  litera "O"  
  {1,1,1,1,1},
  {1,0,0,0,1},
  {1,0,0,0,1},
  {1,1,1,1,1},
  
  //  spacja
  {0,0,0,0,0},
  {0,0,0,0,0}, 
  {0,0,0,0,0},
  
  //  litera "K"
  {0,0,0,0,0},
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,1,0,1,0},
  {1,0,0,0,1},
  
  
  {0,0,0,0,0}
};*/


int time = 10;
int currectState = 0;
int up = true;

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(pin[i], OUTPUT);
  }
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  
  if (currectState == stateNo / 2) {
    analogWrite(pinBuzzer, 10 );
  } else {
    analogWrite(pinBuzzer, 0);
  }
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin[i], state[currectState][i]);
  }
  
  if (up) {
    currectState++;
  } else {
    currectState--;
  }
  
  if (currectState == stateNo) {
    up = false;
    currectState = stateNo - 2;
  }
  if (currectState < 0) {
    up = true;
    currectState = 1;
  }

  delay(time);
  
  if (currectState == 0 || currectState == stateNo) {
    analogWrite(pinBuzzer, 0);
  }
}
