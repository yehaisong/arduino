static const uint8_t analog_pins[] = {A0,A1,A2,A3,A4,A5,A6,A7};
void setup() {
  // put your setup code here, to run once:
  for(int i=2;i<=13;i++)
  {
    pinMode(i,OUTPUT);
  }
  for(int i=0;i<8;i++)
  {
    pinMode(analog_pins[i],OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2;i<=13;i++)
  {
    digitalWrite(i,HIGH);
    delay(100);
    digitalWrite(i,LOW);
    delay(100);
  }
  for(int i=0;i<8;i++)
  {
    digitalWrite(analog_pins[i],HIGH);
    delay(100);
    digitalWrite(analog_pins[i],LOW);
    delay(100);
  }
  delay(500);
}

void blink()
{
}

