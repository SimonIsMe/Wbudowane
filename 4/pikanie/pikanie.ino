
int speakerOut = 9;

void setup() {
  pinMode(speakerOut, OUTPUT);
  beep(50, 50, 31);
  beep(50, 50, 33);
  beep(50, 50, 35);
  delay(1000);
}

void loop() {
  beep(50, 1000, 104);
}


void beep(int signalTime, int waitingTime, int toneLevel) {
  analogWrite(speakerOut, toneLevel);
  delay(signalTime);
  analogWrite(speakerOut, 0);
  delay(waitingTime);
}
