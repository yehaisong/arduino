int motorPin = 9;
int speed=0;
void setup() {
  // put your setup code here, to run once:
pinMode(motorPin, OUTPUT);
Serial.begin(9600);
while(!Serial);
uSerial.println("Speed 0 to 255");


}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  speed=Serial.parseInt();
  if(speed>=0 && speed<=255)
  {
    analogWrite(motorPin,speed);
  }
//  if(Keyboard.press("KEY_UP_ARROW")&&speed<255)
//  {
//    speed+=10;
//  }
//  else if(Keyboard.press("KEY_DOWN_ARROW")&&speed>0)
//  {
//    speed-=10;
//  }
//  
//  analogWrite(motorPin,speed); 
}
}
