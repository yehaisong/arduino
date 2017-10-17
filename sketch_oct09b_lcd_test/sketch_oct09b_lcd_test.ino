#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
  // put your setup code here, to run once:
  //set number of columns and rows
  lcd.begin(16,2);
  lcd.print("hello, world");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);//set column and row
  lcd.print(millis()/1000);
}
