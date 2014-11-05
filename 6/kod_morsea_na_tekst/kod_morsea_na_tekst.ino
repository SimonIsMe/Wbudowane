int pinButton = 2;
int pinLed = 12;
int pinBuzzer = 10;

int dlugoscKropki = 300;  //  maksymalny czas na kropkę w ms
int nacisniecia[5];
int  i = 0;
String tekst = "";

volatile int state = LOW;

long unsigned timeBuffor = 0;
long unsigned time;
long unsigned periodOfTime = 0; // jak długo przycisk był w danym stanie

void setup() {
  Serial.begin(9600);
  
  pinMode(pinButton, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pinButton);
  time = millis();
  
  if (buttonState != state) {
    //  zmieniono stan przycisku
    state = buttonState;

    if (timeBuffor > 0) {
      if (state == HIGH) {
        //Serial.print("Przerwa trwala ");
        //Serial.println(time - timeBuffor);
        
        // jak długa jest przerwa?
        if (time - timeBuffor < dlugoscKropki) {
          //  kontynuuję pisanie kropek i kresek
        } else if (time - timeBuffor < 3 * dlugoscKropki) {
          //  nowa litera
          nacisnieciaNaLitere();
          clearNacisniecia();
          i = 0;
        } else {
          //  nowy wyraz
          nacisnieciaNaLitere();
          clearNacisniecia();
          i = 0;
          tekst = tekst + " ";
        }
      } else {
        //Serial.print("Nacisniecie trwalo trwalo ");
        //Serial.println(time - timeBuffor);
        
        //  jak długo nasiskam
        if (time - timeBuffor < dlugoscKropki) {
          nacisniecia[i] = 1;
        } else {
          nacisniecia[i] = 2;
        }
        i++;
        Serial.print(">>>   ");
        Serial.println(i);
      }
    }

    timeBuffor = time;
  }
  
  digitalWrite(pinLed, state);
  if (state == HIGH) {
    analogWrite(pinBuzzer, 100);
  } else {
    analogWrite(pinBuzzer, 0);
  }
  
  delay(10);
}

void clearNacisniecia() 
{
  for (int k = 0; k < 5; k++) {
    nacisniecia[k] = -1;
  }
}

void nacisnieciaNaLitere()
{
  
  //Serial.print("znakow ");
  //Serial.println(i);
  
  /*for (int k = 0; k < i; k++) {
    Serial.print(" ");
    Serial.print(nacisniecia[k]);
  }
  Serial.println("");*/
  
  if (i == 1) {
    if (nacisniecia[0] == 1) {
      tekst = tekst + "E";
    } else {
      tekst = tekst + "T";
    }
  } else if (i == 2) {
    if (nacisniecia[0] == 1 && nacisniecia[1] == 1) {
      tekst = tekst + "I";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1) {
      tekst = tekst + "N";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2) {
      tekst = tekst + "M";
    }
  } else if (i == 3) {
    if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1) {
      tekst = tekst + "S";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 2) {
      tekst = tekst + "O";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 1) {
      tekst = tekst + "R";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 2) {
      tekst = tekst + "U";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 2) {
      tekst = tekst + "W";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 1) {
      tekst = tekst + "D";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 1) {
      tekst = tekst + "G";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 2) {
      tekst = tekst + "K";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 2) {
      tekst = tekst + "U";
    }
  } else if (i == 4) {
    if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 1) {
      tekst = tekst + "B";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 2 && nacisniecia[3] == 1) {
      tekst = tekst + "C";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 2 && nacisniecia[3] == 1) {
      tekst = tekst + "F";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 1) {
      tekst = tekst + "H";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 2) {
      tekst = tekst + "J";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 1 && nacisniecia[3] == 1) {
      tekst = tekst + "L";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 1) {
      tekst = tekst + "P";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 1 && nacisniecia[3] == 2) {
      tekst = tekst + "Q";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 2) {
      tekst = tekst + "V";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 2) {
      tekst = tekst + "X";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 2 && nacisniecia[3] == 2) {
      tekst = tekst + "Y";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 1 && nacisniecia[3] == 1) {
      tekst = tekst + "Z";
    }
  } else if (i == 5) {
    if (nacisniecia[0] == 1 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 2 && nacisniecia[4] == 2) {
      tekst = tekst + "1";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 2 && nacisniecia[3] == 2 && nacisniecia[4] == 2) {
      tekst = tekst + "2";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 2 && nacisniecia[4] == 2) {
      tekst = tekst + "3";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 1 && nacisniecia[4] == 2) {
      tekst = tekst + "4";
    } else if (nacisniecia[0] == 1 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 1 && nacisniecia[4] == 1) {
      tekst = tekst + "5";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 1 && nacisniecia[2] == 1 && nacisniecia[3] == 1 && nacisniecia[4] == 1) {
      tekst = tekst + "6";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 1 && nacisniecia[3] == 1 && nacisniecia[4] == 1) {
      tekst = tekst + "7";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 1 && nacisniecia[4] == 1) {
      tekst = tekst + "8";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 2 && nacisniecia[4] == 1) {
      tekst = tekst + "9";
    } else if (nacisniecia[0] == 2 && nacisniecia[1] == 2 && nacisniecia[2] == 2 && nacisniecia[3] == 2 && nacisniecia[4] == 2) {
      tekst = tekst + "0";
    }
  }
  
  
  Serial.println(tekst);
}
