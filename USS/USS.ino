
#include <NewPing.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define TRIGGER_PIN  8
#define ECHO_PIN     9
#define MAX_DISTANCE 200
int Start=0;
float LastDistance=0;
float CurrentDistance=0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
pinMode (13,INPUT);
//float uS = sonar.ping();
//LastDistance=(round(uS/US_ROUNDTRIP_IN*4)/4.0);
//CurrentDistance=(round(uS/US_ROUNDTRIP_IN*4)/4.0);
  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   // Print a message to the LCD.
   lcd.print("Distance (IN)");
}

void loop() {
  delay(1000);
  float uS = sonar.ping();
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_IN);
  Serial.println("in");
  lcd.setCursor(0, 1);
 // CurrentDistance=(round(uS/US_ROUNDTRIP_IN*4)/4.0);
  lcd.print(round(uS/US_ROUNDTRIP_IN*4)/4.0);
/* if(Start==1){
    lcd.print(LastDistance-CurrentDistance);
    //delay(5000);
  }
  else{
    if(LastDistance-CurrentDistance>0.5){
      Start=1;
    }
    else{
      LastDistance=CurrentDistance;
    }
  }
  
  if(digitalRead(13)==HIGH){
    Start=0;
  }*/
}


