/* YourDuinoStarter Example: nRF24L01 Radio remote control of servos by joystick
  - WHAT IT DOES
   Joystick on other Arduino communicates by nRF25L01 Radio to
   this Arduino with 2 pan-tilt servos
   SEE: The variable 'hasHardware'. You can test without servos and later set hasHardware = true;
        You NEED separate Servo power, not USB. YourDuino RoboRED has built in 2A power for servos
  - SEE the comments after "//" on each line below
  - CONNECTIONS:
   - nRF24L01 Radio Module: See http://arduino-info.wikispaces.com/Nrf24L01-2.4GHz-HowTo
   1 - GND
   2 - VCC 3.3V !!! NOT 5V
   3 - CE to Arduino pin 7
   4 - CSN to Arduino pin 8
   5 - SCK to Arduino pin 13
   6 - MOSI to Arduino pin 11
   7 - MISO to Arduino pin 12
   8 - UNUSED

  - V2.12 02/08/2016
   - Uses the RF24 Library by TMRH20 and Maniacbug: https://github.com/TMRh20/RF24 (Download ZIP)
   Questions: terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include "printf.h" // Needed for "printDetails" Takes up some memory
// NEED the SoftwareServo library installed
// http://playground.arduino.cc/uploads/ComponentLib/SoftwareServo.zip
//#include <SoftwareServo.h>  // Regular Servo library creates timer conflict!
/*-----( Declare Constants and Pin Numbers )-----*/
#define  CE_PIN  9   // The pins to be used for CE and SN
#define  CSN_PIN 10

const int redPin=11;
const int greenPin=12;
const int bluePin=13;
const int forward=4;
const int reverse=5;
const int left=8;
const int right=7;
const int radioled=6;
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

/*-----( Declare objects )-----*/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

//SoftwareServo HorizontalServo;
//SoftwareServo VerticalServo;  // create servo objects to control servos

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

// Allows testing of radios and code without servo hardware. Set 'true' when servos connected
boolean hasHardware = false;  // Allows testing of radios and code without Joystick hardware.
//boolean hasHardware = true;

int HorizontalJoystickReceived; // Variable to store received Joystick values
int HorizontalServoPosition;    // variable to store the servo position

int VerticalJoystickReceived;   // Variable to store received Joystick values
int VerticalServoPosition;      // variable to store the servo positio

/**
  Create a data structure for transmitting and receiving data
  This allows many variables to be easily sent and received in a single transmission
  See http://www.cplusplus.com/doc/tutorial/structures/
*/
struct dataStruct {
  unsigned long _micros;  // to save response times
  int Xposition;          // The Joystick position values
  int Yposition;
  bool switchOn;          // The Joystick push-down switch
} myData;                 // This can be accessed in the form:  myData.Xposition  etc.



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);// MUST reset the Serial Monitor to 115200 (lower right of window )
  // NOTE: The "F" in the print statements means "unchangable data; save in Flash Memory to conserve SRAM"
  Serial.println(F("YourDuino.com Example: Receive joystick data by nRF24L01 radio from another Arduino"));
  Serial.println(F("and control servos if attached (Check 'hasHardware' variable)"));
  printf_begin(); // Needed for "printDetails" Takes up some memory
  /*-----( Set up servos )-----*/
  if (hasHardware)
  {
    //HorizontalServo.attach(ServoHorizontalPIN);  // attaches the servo to the servo object
    //VerticalServo.attach(ServoVerticalPIN);
  }

  radio.begin();          // Initialize the nRF24L01 Radio
  radio.setChannel(108);  // 2.508 Ghz - Above most Wifi Channels
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range

  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  //   radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

  // Start the radio listening for data
  radio.startListening();
  radio.printDetails(); //Uncomment to show LOTS of debugging information
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, LOW);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  pinMode(left,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(radioled,OUTPUT);

  digitalWrite(forward, LOW);
  digitalWrite(reverse,LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);

  digitalWrite(radioled, LOW);
}

int number=0;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    controlbySerialCMD();
  }
//  int joystick=digitalRead(SW_pin);
//  if(joystick==1)
//  {
//    controlbyJoystick();
//  }

  radio.startListening();
  //Serial.print(radio.available());
  if ( radio.available())
  {
    while (radio.available())   // While there is data ready to be retrieved from the receive pipe
    {
      radio.read( &myData, sizeof(myData) );             // Get the data
    }

    //radio.stopListening();                               // First, stop listening so we can transmit
    //radio.write( &myData, sizeof(myData) );              // Send the received data back.
    //radio.startListening();                              // Now, resume listening so we catch the next packets.

    Serial.print(F("Packet Received "));//- Sent response "));  // Print the received packet data
    Serial.print(myData._micros);
    Serial.print(F("uS X= "));
    Serial.print(myData.Xposition);
    Serial.print(F(" Y= "));
    Serial.print(myData.Yposition);
    if ( myData.switchOn == 1)
    {
      Serial.println(F(" Switch ON"));
    }
    else
    {
      Serial.println(F(" Switch OFF"));
    }

    controlbyJoystick(myData.Xposition,myData.Yposition);
    // END radio available
  } 
  else
  {
    ss();
  }
  delay(10);
}

void controlbySerialCMD()
{
      String s=Serial.readStringUntil('/');

    String cmd=s.substring(0,1);
    if(cmd=="1")
    {
      int ri=s.indexOf(' ');
      int red=s.substring(1,ri).toInt();
      int gi=s.indexOf(' ',ri+1);
      int green=s.substring(ri+1,gi).toInt();
      int blue=s.substring(gi+1).toInt();
      
      Serial.println(s);
      Serial.println(ri);
      Serial.println(gi);
      Serial.println(red);
      Serial.println(green);
      Serial.println(blue);
      
      light(red,green,blue);
    }
    else if (cmd=="2")
    {
      String action=s.substring(1);
      Serial.println(action);
      car_action(action);
    }
}


void controlbyJoystick(int xPosition, int yPosition)
{
  int x=xPosition;
  int y=yPosition;

  String ax="s";
  String ay="s";

  if(x<100)
  {
    ax="f";
  }
  else if(x>800)
  {
    ax="r";
  }
  else
  {
    ax="s";
  }

  if(y<100)
  {
    ay="r";
  }
  else if(y>800)
  {
    ay="l";
  }
  else
  {
    ay="s";
  }

 String joystickcmd=ax+ay;
 car_action(joystickcmd);
 if(joystickcmd!="ss")
 {
  digitalWrite(radioled, HIGH);
 }
 else
 {
  digitalWrite(radioled,LOW);
 }
}

void car_action(String action)
{
    if(action=="fl")
      {
        fl();
      }
      else if(action=="fr")
      {
        fr();
      }
      else if(action=="fs")
      {
        fs();
      }
      else if(action=="rl")
      {
        rl();
      }
      else if(action=="rr")
      {
        rr();
      }
      else if(action=="rs")
      {
        rs();
      }
      else if(action=="sl")
      {
        sl();
      }
      else if(action=="sr")
      {
        sr();
      }
      else if(action=="ss")
      {
        ss();
      }
      else
      {
        ss();
      }
}
  


void fl()
{
  digitalWrite(forward, HIGH);
        digitalWrite(reverse,LOW);
        digitalWrite(left, HIGH);
        digitalWrite(right,LOW);
}

void fr()
{
  digitalWrite(forward, HIGH);
        digitalWrite(reverse,LOW);
        digitalWrite(left, LOW);
        digitalWrite(right,HIGH);
}


void fs()
{
  digitalWrite(forward, HIGH);
        digitalWrite(reverse,LOW);
        digitalWrite(left, LOW);
        digitalWrite(right,LOW);
}

void rl()
{
  digitalWrite(forward, LOW);
        digitalWrite(reverse,HIGH);
        digitalWrite(left, HIGH);
        digitalWrite(right,LOW);
}


void rr()
{
  digitalWrite(forward, LOW);
        digitalWrite(reverse,HIGH);
        digitalWrite(left, LOW);
        digitalWrite(right,HIGH);
}

void rs()
{
  digitalWrite(forward, LOW);
        digitalWrite(reverse,HIGH);
        digitalWrite(left, LOW);
        digitalWrite(right,LOW);
}

void sl()
{
  digitalWrite(forward, LOW);
        digitalWrite(reverse,LOW);
        digitalWrite(left, HIGH);
        digitalWrite(right,LOW);
}

void sr()
{
          digitalWrite(forward, LOW);
        digitalWrite(reverse,LOW);
        digitalWrite(left, LOW);
        digitalWrite(right,HIGH);
}

void ss()
{
  digitalWrite(forward, LOW);
  digitalWrite(reverse,LOW);
  digitalWrite(left, LOW);
  digitalWrite(right,LOW);
}
void light(int r, int g, int b)
{
  analogWrite(redPin, 255-r);
  analogWrite(greenPin, 255-g);
  analogWrite(bluePin, 255-b);
}

