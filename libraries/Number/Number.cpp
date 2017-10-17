/*Number.cpp*/
#include "Arduino.h"
#include "Number.h"

Number::Number(int dataPin, int clockPin, int latchPin)
{
  _datapin=dataPin;
  _clockpin=clockPin;
  _latchpin=latchPin;
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void Number::On()
{
  digitalWrite(_latchpin, 1);
}

void Number::Off()
{
  digitalWrite(_latchpin, 0);
}

void Number::Display(int number)
{
  Off();
  byte bitsToSend = 0;
  switch (number)
  {
    case 0:
        //0
      bitsToSend = 0x3F;
      break;
    case 1:
        //1
      bitsToSend = 0x6;
      break;
    case 2:
        //2
      bitsToSend = 0x5B;
      break;
    case 3:
        //3
      bitsToSend = 0x4F;
      break;
    case 4:
        //4
      bitsToSend = 0x66;
      break;
    case 5:
        //5
      bitsToSend = 0x6D;
      break;
    case 6:
        //6
      bitsToSend = 0x7D;
      break;
    case 7:
        //7
      bitsToSend = 0x7;
      break;
    case 8:
        //8
      bitsToSend = 0x7F;
      break;
    case 9:
        //9
      bitsToSend = 0x6F;
      break;
  }
  shiftOut(_datapin, _clockpin, MSBFIRST, bitsToSend);
  On();
}

