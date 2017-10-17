int latchPin = 12;  //Pin connected to ST_CP of 1st 74595
int clockPin = 13;  //Pin connected to SH_CP of 1st 74595
int dataPin = 11;   //Pin connected to DS of 1st 74595

int latchPin2 = 6;  //Pin connected to ST_CP of 2nd 74595
int clockPin2 = 7;  //Pin connected to SH_CP of 2nd 74595
int dataPin2 = 5;   //Pin connected to DS of 2nd 74595

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(latchPin2, OUTPUT);
  pinMode(clockPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);
}

void loop() {
  //turnoffall();
   int i=11;
   while(i>=0)
   {
     turnoffall();
     for(int x=0;x<25;x++)
     {
       turnoffall();
       lights(pow(2,i),0b01111110);
       //delay(1);
       
       turnoffall();
       lights(pow(2,i-1),0b10111101);
       //delay(1);
    
       turnoffall();
       lights(pow(2,i-2),0b11011011);
       //delay(1);
    
       turnoffall();
       lights(pow(2,i-3),0b11100111);
       //delay(1);
     }
     i--;
     
   }
//delay(1000);
}

void lights(int anode, int cathode)
{
   /*** Send HIGH to all cathode pins (4, 7, 2, 8, 12, 1, 14 and 9) of LED matrix ***/  
    // take the latchPin low so the LEDs don't change while you're sending in bits:  
    digitalWrite(latchPin, LOW);
    //Send 0 0 0 0 0 0 0 0 (1) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 1st 74595
    shiftOut(dataPin, clockPin, MSBFIRST, cathode);
    // shift out the bits:    
    digitalWrite(latchPin, HIGH);

    /*** Send LOW to all Anode pins (16, 15, 11, 3, 10, 5, 6, 13) of LED matrix ***/   
    // take the latchPin low so the LEDs don't change while you're sending in bits:    
    digitalWrite(latchPin2, LOW);
    //Send 1 1 1 1 1 1 1 1 (255) to Q7 Q6 Q5 Q4 Q3 Q2 Q1 Q0 of 2nd 74595
    shiftOut(dataPin2, clockPin2, MSBFIRST,anode);
    // shift out the bits:  
    digitalWrite(latchPin2, HIGH);
}

void turnoffall()
{
      /**************************  TURN OFF ALL LEDs  ***************************/    
    
   lights(0b00000000,0b11111111);
}


