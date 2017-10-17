

// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = 0;
int outSensorPin=1;
int Rpin=7;
int Gpin=8;
int Bpin=9;
int flag=0;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(13,INPUT);
   // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   // Print a message to the LCD.
   lcd.print("Temperature(C/F)");

  // put your setup code here, to run once:;
  //Serial.begin(9600);

}


void loop() {
    float tc=0;
    if(digitalRead(13)==LOW)
    {
      if(flag==0)
      {
        flag=1;
        // set up the LCD's number of columns and rows:
         lcd.begin(16, 2);
         // Print a message to the LCD.
         lcd.print("Indoor Temp(C/F)");
      }
      else if(flag==1)
      {
        flag=0;
        // set up the LCD's number of columns and rows:
         lcd.begin(16, 2);
         // Print a message to the LCD.
         lcd.print("Outdoor Temp(C/F)");
      }
    }
    //Serial.print(flag);
    if(flag==0)
    {
      tc=getOutDoorTemp();
    }
    else if(flag==1)
    {
      tc=getInDoorTemp();
    }
    float temperatureF = (tc * 9.0 / 5.0) + 32.0;
    float tf=temperatureF;
    //Serial.print(temperatureF); Serial.println(" degrees F");
    
    
// set the cursor to column 0, line 1
   // (note: line 1 is the second row, since counting begins with 0):
   lcd.setCursor(0, 1);
   // print the number of seconds since reset:
   lcd.print(String(tc)+"/" +String(tf));
   if(tc>35)
   {
    setcolor(0,255,0);
   }
   else if(tc>=30 && tc<=35)
   {
    setcolor(0,255,0);
   }
    else if(tc>=20 && tc<=30)
   {
    setcolor(0,255,0);
   }
    else if(tc>=10 && tc<=20)
   {
    setcolor(0,255,100);
   }
    else if(tc>=0 && tc<=10)
   {
    setcolor(0,0,100);
   }
    else if(tc>=-10 && tc<=0)
   {
    setcolor(255,0,100);
   }
    else if(tc<-10)
   {
    setcolor(100,0,100);
   }
  
    delay(1000);

}

float getOutDoorTemp()
{
  float temperatureC=0;
  int reading = analogRead(outSensorPin);
    for (int i=0;i<50;i++)
    {
      int r=analogRead(outSensorPin);
      reading=reading+r;
    }
    reading=reading/51;
    float voltage = reading * 5.0;
    voltage /= 1024.0;  
    //Serial.print(voltage); Serial.println("volts");
    temperatureC = (voltage - 0.5) * 100;
    //Serial.print(temperatureC); Serial.println(" degrees C");
    return temperatureC;
}

float getInDoorTemp()
{
  float temperatureC=0;
  int reading = analogRead(sensorPin);
    for (int i=0;i<50;i++)
    {
      int r=analogRead(sensorPin);
      reading=reading+r;
    }
    reading=reading/51;
    float voltage = reading * 5.0;
    voltage /= 1024.0;  
    //Serial.print(voltage); Serial.println("volts");
    //float temperatureC = (voltage - 0.5) * 100;
    temperatureC = (voltage) * 100;
    //Serial.print(temperatureC); Serial.println(" degrees C");
    return temperatureC-2.5;
}
void setcolor (int r,int g,int b)
{
  analogWrite(Rpin,r);
  analogWrite(Gpin,g);
  analogWrite(Bpin,b);
}


