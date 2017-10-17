#define Rpin 11
#define Gpin 10
#define Bpin 9

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  setcolor(0,80,80);
  delay(1000);
  setcolor(255,0,0);
  delay(1000);
  setcolor(200,0,0);
  delay(1000);
  setcolor(100,0,0);
  delay(1000);
  setcolor(50,0,0);
  delay(1000);
  
}

void setcolor(int r,int g,int b)
{
  analogWrite(Rpin,r);
  analogWrite(Gpin,g);
  analogWrite(Bpin,b);
}
