int sensorPin = 0;

// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
   // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   // Print a message to the LCD.
   lcd.print("Temperature(C/F)");

  // put your setup code here, to run once:;
  //Serial.begin(9600);

}


void loop() {

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
    float temperatureC = (voltage) * 100;
    //Serial.print(temperatureC); Serial.println(" degrees C");
    float tc=temperatureC+2;
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    float tf=temperatureF;
    //Serial.print(temperatureF); Serial.println(" degrees F");
    
    
// set the cursor to column 0, line 1
   // (note: line 1 is the second row, since counting begins with 0):
   lcd.setCursor(0, 1);
   // print the number of seconds since reset:
   lcd.print(String(tc)+"/" +String(tf));

    delay(5000);

}


