const int redPin=11;
const int greenPin=12;
const int bluePin=13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int number=0;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    char ch=Serial.readStringUntil(e);

    Serial.println(ch);
    
    if(ch=='r')
    {
      light(0,255,255);
    }
    else if(ch=='g')
    {
      light(255,0,255);
    }
    else if(ch=='b')
    {
      light(255,255,0);
    }
    else
    {
      light(255,255,255);
    }
  }
  

  
  delay(10);
  number++;
}

void light(int r, int g, int b)
{
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}

