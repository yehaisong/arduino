/*Number.h*/
#ifndef Number_h
#define Number_h
#include "Arduino.h"

class Number
{
  public:
    Number(int dataPin, int clockPin, int latchPin);
    void Display(int number);
    void On();
    void Off();
   private:
    int _datapin;
    int _clockpin;
    int _latchpin;
};
#endif

