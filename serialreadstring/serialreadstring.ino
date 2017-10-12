#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const int redPin=11;
const int greenPin=12;
const int bluePin=13;
const int forward=4;
const int reverse=5;
const int left=8;
const int right=9;
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, LOW);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  pinMode(left,OUTPUT);
  pinMode(right,OUTPUT);
}

int number=0;

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    controlbySerialCMD();
  }
  int joystick=digitalRead(SW_pin);
  if(joystick==1)
  {
    controlbyJoystick();
  }

  
  delay(10);
  number++;
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


void controlbyJoystick()
{
  int x=analogRead(X_pin);
  int y=analogRead(Y_pin);

  String ax="s";
  String ay="s";

  if(x<10)
  {
    ax="f";
  }
  else if(x>1000)
  {
    ax="r";
  }
  else
  {
    ax="s";
  }

  if(y<10)
  {
    ay="r";
  }
  else if(y>1000)
  {
    ay="l";
  }
  else
  {
    ay="s";
  }

 String joystickcmd=ax+ay;
 car_action(joystickcmd);
  
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

