#include <Number.h>
Number num(11,12,8);
const int D1=9;
const int D2=10;

void setup() {
  // put your setup code here, to run once:
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 // num.Display(19);
  display2Dig(23);
}

void display2Dig(int number)
{
  if(number>=0&&number<=99)
  {
    int dig2=number/10;
    int dig1=number%10;
    //Serial.println(dig2);
    //Serial.println(dig1);
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    num.Display(dig1);
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    num.Display(dig2);
  }
}

