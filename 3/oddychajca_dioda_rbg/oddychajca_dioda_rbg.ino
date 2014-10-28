
int red = 11; 
int blue = 9; 
int green = 10; 

int valueRed;
int valueGreen;
int valueBlue;

int percent = 0;
int prevPercent = 0;

float time = 3.14 * 1.50;

boolean isDown = false;

void setup() 
{
  pinMode(red, OUTPUT);
  analogWrite(red, 255); 

  pinMode(green, OUTPUT);
  analogWrite(green, 255);
  
  pinMode(blue, OUTPUT);
  analogWrite(blue, 255);
  
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  
  losujKolory();
}

void loop() 
{ 
  time += 0.01;
  
  float sinY = sin(time) + 1;
  
  Serial.println(sinY);
  
  prevPercent = percent;
  percent = sinY * 50;
  
  if (percent == 0 && prevPercent != 0) {
    losujKolory();
  }
  
  analogWrite(red, 255 - valueRed * percent / 100); 
  analogWrite(green, 255 - valueGreen * percent / 100);
  analogWrite(blue, 255 - valueBlue * percent / 100);
  
  delay(10);
} 

void losujKolory() 
{
  valueRed = random(256);
  valueGreen = random(256);
  valueBlue = random(256);
}
