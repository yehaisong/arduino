

int RED_PIN=2;
int GREEN_PIN=3;
int BLUE_PIN=4;
int RED_PIN1=7;
int GREEN_PIN1=8;
int BLUE_PIN1=9;
int RED_PIN2=11;
int GREEN_PIN2=12;
int BLUE_PIN2=13;


void setup() {
   pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
   pinMode(RED_PIN1, OUTPUT);
  pinMode(GREEN_PIN1, OUTPUT);
  pinMode(BLUE_PIN1, OUTPUT);
 pinMode(RED_PIN2, OUTPUT);
  pinMode(GREEN_PIN2, OUTPUT);
  pinMode(BLUE_PIN2, OUTPUT);
}


void loop() {
   showSpectrum();
}

void showSpectrum()
{
  int x;  // define an integer variable called "x"
  
  // Now we'll use a for() loop to make x count from 0 to 767
  // (Note that there's no semicolon after this line!
  // That's because the for() loop will repeat the next
  // "statement", which in this case is everything within
  // the following brackets {} )

  for (x = 768; x >= 0; x--)

  // Each time we loop (with a new value of x), do the following:

  {
    showRGB(x);  // Call RGBspectrum() with our new x
    delay(10);   // Delay for 10 ms (1/100th of a second)
  }
}


// showRGB()

// This function translates a number between 0 and 767 into a
// specific color on the RGB LED. If you have this number count
// through the whole range (0 to 767), the LED will smoothly
// change color through the entire spectrum.

// The "base" numbers are:
// 0   = pure red
// 255 = pure green
// 511 = pure blue
// 767 = pure red (again)

// Numbers between the above colors will create blends. For
// example, 640 is midway between 512 (pure blue) and 767
// (pure red). It will give you a 50/50 mix of blue and red,
// resulting in purple.

// If you count up from 0 to 767 and pass that number to this
// function, the LED will smoothly fade between all the colors.
// (Because it starts and ends on pure red, you can start over
// at 0 without any break in the spectrum).


void showRGB(int color)
{
  int redIntensity;
  int greenIntensity;
  int blueIntensity;

  // Here we'll use an "if / else" statement to determine which
  // of the three (R,G,B) zones x falls into. Each of these zones
  // spans 255 because analogWrite() wants a number from 0 to 255.

  // In each of these zones, we'll calculate the brightness
  // for each of the red, green, and blue LEDs within the RGB LED.

  if (color >= 512)          // zone 1
  {
    redIntensity = color - 512;    // red goes from on to off
    greenIntensity = 255 - (color - 512);        // green goes from off to on
    blueIntensity = 255;             // blue is always off
  }
  else if (color >=256)     // zone 2
  {
    redIntensity = 255;                     // red is always off
    greenIntensity = color - 256; // green on to off
    blueIntensity = 255 - (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 256);         // red off to on
    greenIntensity = 255;                   // green is always off
    blueIntensity = 255 - color;  // blue on to off
  }

  // Now that the brightness values have been set, command the LED
  // to those values

  analogWrite(RED_PIN, redIntensity);
  analogWrite(BLUE_PIN, blueIntensity);
  analogWrite(GREEN_PIN, greenIntensity);
  analogWrite(RED_PIN1, greenIntensity);
  analogWrite(BLUE_PIN1, blueIntensity);
  analogWrite(GREEN_PIN1, redIntensity);
  analogWrite(RED_PIN2, blueIntensity);
  analogWrite(BLUE_PIN2, greenIntensity);
  analogWrite(GREEN_PIN2, redIntensity);
}
