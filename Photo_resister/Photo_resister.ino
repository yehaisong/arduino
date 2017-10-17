void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int lightLevel=analogRead(A0);
  lightLevel=map(lightLevel,0,1023,0,255);
  digitalWrite(9,lightLevel);
  if(lightLevel>=125)
  {
    digitalWrite(9,125);
  }
  else
  {
    digitalWrite(9,LOW);
  }
  if(lightLevel>=150)
  {
    digitalWrite(9,HIGH);
  }
}
