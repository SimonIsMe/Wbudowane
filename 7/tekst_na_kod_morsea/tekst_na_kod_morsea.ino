int incomingByte = 0;

int pinBuzzer = 10;
int pinLed = 12;

int dlugoscKropki = 100;  //  maksymalny czas na kropkę w ms

void setup() {
  Serial.begin(9600);
  
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    
    incomingByte = Serial.read();
    
    if (incomingByte >= 65 && incomingByte <= 90) {
      //  wielkie litery
      incomingByte += 'a' - 'A';
    }
    
    if (!(incomingByte >= 97 && incomingByte <= 122) && incomingByte != 32) {
      Serial.println("Nieobslugiwany znak");
      return;
    }
    
    Serial.print("Zwracam litere: ");
    Serial.println((char) incomingByte);
    switch (incomingByte) {
      case 'a': 
        beeps(1, 2, 0, 0);
        break;
      case 'b': 
        beeps(2, 1, 1, 1);
        break;
      case 'c': 
        beeps(2, 1, 2, 1);
        break;
      case 'd': 
        beeps(2, 1, 1, 0);
        break;
      case 'e': 
        beeps(1, 0, 0, 0);
        break;
      case 'f': 
        beeps(1, 1, 2, 1);
        break;
      case 'g': 
        beeps(2, 2, 1, 0);
        break;
      case 'h': 
        beeps(1, 1, 1, 1);
        break;
      case 'i': 
        beeps(1, 1, 0, 0);
        break;
      case 'j': 
        beeps(1, 2, 2, 2);
        break;
      case 'k': 
        beeps(2, 1, 2, 0);
        break;
      case 'l': 
        beeps(1, 2, 1, 1);
        break;
      case 'm': 
        beeps(2, 2, 0, 0);
        break;
      case 'n': 
        beeps(2, 1, 0, 0);
        break;
      case 'o': 
        beeps(2, 2, 2, 0);
        break;
      case 'p': 
        beeps(1, 2, 2, 1);
        break;
      case 'q': 
        beeps(2, 2, 1, 2);
        break;
      case 'r': 
        beeps(1, 2, 1, 0);
        break;
      case 's': 
        beeps(1, 1, 1, 0);
        break;
      case 't': 
        beeps(2, 0, 0, 0);
        break;
      case 'u': 
        beeps(1, 1, 2, 0);
        break;
      case 'v': 
        beeps(1, 1, 1, 2);
        break;
      case '2': 
        beeps(1, 2, 2, 0);
        break;
      case 'x': 
        beeps(2, 1, 1, 2);
        break;
      case 'y': 
        beeps(2, 1, 2, 2);
        break;
      case 'z': 
        beeps(2, 2, 1, 1);
        break;
    }
    
    delay(dlugoscKropki * 3 * 2);
  }
}

void beeps(int type0, int type1, int type2, int type3)
{
  int types[4];
  types[0] = type0;
  types[1] = type1;
  types[2] = type2;
  types[3] = type3;
  
  for (int i = 0; i < 4; i++) {
    if (types[i] == 0) {
      break;
    }
    
    if (types[i] == 1) {
      //  kropka
      analogWrite(pinBuzzer, 30);
      digitalWrite(pinLed, HIGH);
      delay(dlugoscKropki);
      analogWrite(pinBuzzer, 0);
      digitalWrite(pinLed, LOW);
      delay(dlugoscKropki);
    } else {
      //  kreska
      analogWrite(pinBuzzer, 30);
      digitalWrite(pinLed, HIGH);
      delay(dlugoscKropki * 3);
      digitalWrite(pinLed, LOW);
      analogWrite(pinBuzzer, 0);
      delay(dlugoscKropki);
    }
  }
}

