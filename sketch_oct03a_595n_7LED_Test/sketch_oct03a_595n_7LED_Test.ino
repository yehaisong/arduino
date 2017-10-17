#include <Number.h>

//Pin connected to latch pin (ST_CP) of 74HC595
int latchPin = 8;
//Pin connected to clock pin (SH_CP) of 74HC595
int clockPin = 12;
////Pin connected to Data in (DS) of 74HC595
int dataPin = 11;

Number num(dataPin, clockPin, latchPin);

void setup() {
  // put your setup code here, to run once:
  //set pins to output because they are addressed in the main loop

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=9;i>=0;i--)
  {
    num.Display(i);
    delay(1000);
  }
}
