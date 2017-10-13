#include <FastLED.h>

#define LED_PIN     6    //led strand is soldered to pin 6
#define NUM_LEDS    10   // number of LEDs in my strand
#define COLOR_ORDER GRB

uint8_t brightness = 255;  //led strand brightness control
uint8_t cpbrightness = 40;  //circuit playground brightness control

int STEPS = 25;  //makes the rainbow colors more or less spread out
int NUM_MODES = 5;  // change this number if you add or subtract modes

CRGB leds[NUM_LEDS];  //I've set up different arrays for the neopixel strand and the circuit playground

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

int ledMode = 0;       //Initial mode 

// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                                  R   G   B
uint8_t myFavoriteColors[][3] = {{200,   100,   200},   // I've set this for pastel twinkles
                                 {200,   200,   100},   // Change colors by inputting diferent R, G, B values on these lines
                                 {100,   200,   200},   //
                               };
// don't edit the line below
#define FAVCOLORS sizeof(myFavoriteColors) / 3



void setup() {
  Serial.begin(57600);
  //CircuitPlayground.begin();
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  currentBlending = LINEARBLEND;
  set_max_power_in_volts_and_milliamps(5, 500);               // FastLED 2.1 Power management set at 5V, 500m
}

void loop()  {

  
    ledMode=5;
    
  
 switch (ledMode) {
       case 0: currentPalette = RainbowColors_p; rainbow(); break; 
       case 1: //motion(); break;
       case 2: //soundreactive(); break; 
       case 3: currentPalette = OceanColors_p; rainbow(); break;                    
       case 4: currentPalette = LavaColors_p; rainbow(); break; 
       case 5: currentPalette = RainbowStripeColors_p; rainbow(); break;    
       case 99: clearpixels(); break;
       
}
}

void clearpixels()
{
  //CircuitPlayground.clearPixels();
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB::Black; 
  //for (int i = 0; i < NUM_CP; i++) cp[i] = CRGB::Black;
  FastLED.show();
}

void rainbow()
{
  
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  FillLEDsFromPaletteColors( startIndex);

  FastLED.show();
  FastLED.delay(10);}

//this bit is in every palette mode, needs to be in there just once
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{ 
  for (int i = 0; i < NUM_LEDS; i++) leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
  //for (int i = 0; i < NUM_CP; i++) cp[i] = ColorFromPalette( currentPalette, colorIndex, cpbrightness, currentBlending);
    colorIndex += STEPS;
  
}


//void soundreactive() {
//
//  uint8_t  i;
//  uint16_t minLvl, maxLvl;
//  int      n, height;
//   
//  n = analogRead(MIC_PIN);                                    // Raw reading from mic
//  n = abs(n - 512 - DC_OFFSET);                               // Center on zero
//  
//  n = (n <= NOISE) ? 0 : (n - NOISE);                         // Remove noise/hum
//  lvl = ((lvl * 7) + n) >> 3;                                 // "Dampened" reading (else looks twitchy)
// 
//  // Calculate bar height based on dynamic min/max levels (fixed point):
//  height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);
// 
//  if (height < 0L)       height = 0;                          // Clip output
//  else if (height > TOP) height = TOP;
//  if (height > peak)     peak   = height;                     // Keep 'peak' dot at top
// 
// 
//  // Color pixels based on rainbow gradient -- led strand
//  for (i=0; i<NUM_LEDS; i++) {
//    if (i >= height)   leds[i].setRGB( 0, 0,0);
//    else leds[i] = CHSV(map(i,0,NUM_LEDS-1,0,255), 255, brightness);  //constrain colors here by changing HSV values
//  }
// 
//  // Draw peak dot  -- led strand
//  if (peak > 0 && peak <= NUM_LEDS-1) leds[peak] = CHSV(map(peak,0,NUM_LEDS-1,0,255), 255, brightness);
//
//  // Color pixels based on rainbow gradient  -- circuit playground
//  for (i=0; i<NUM_CP; i++) {
//    if (i >= height)   cp[i].setRGB( 0, 0,0);
//    else cp[i] = CHSV(map(i,0,NUM_CP-1,0,255), 255, cpbrightness);  //constrain colors here by changing HSV values
//  }
// 
//  // Draw peak dot  -- circuit playground
//  if (peak > 0 && peak <= NUM_CP-1) cp[peak] = CHSV(map(peak,0,NUM_LEDS-1,0,255), 255, cpbrightness);
//
//// Every few frames, make the peak pixel drop by 1:
// 
//    if (++dotCount >= PEAK_FALL) {                            // fall rate 
//      if(peak > 0) peak--;
//      dotCount = 0;
//    }
//  
//  vol[volCount] = n;                                          // Save sample for dynamic leveling
//  if (++volCount >= SAMPLES) volCount = 0;                    // Advance/rollover sample counter
// 
//  // Get volume range of prior frames
//  minLvl = maxLvl = vol[0];
//  for (i=1; i<SAMPLES; i++) {
//    if (vol[i] < minLvl)      minLvl = vol[i];
//    else if (vol[i] > maxLvl) maxLvl = vol[i];
//  }
//  // minLvl and maxLvl indicate the volume range over prior frames, used
//  // for vertically scaling the output graph (so it looks interesting
//  // regardless of volume level).  If they're too close together though
//  // (e.g. at very low volume levels) the graph becomes super coarse
//  // and 'jumpy'...so keep some minimum distance between them (this
//  // also lets the graph go to zero when no sound is playing):
//  if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
//  minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6;                 // Dampen min/max levels
//  maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6;                 // (fake rolling average)
//
//
//show_at_max_brightness_for_power();                         // Power managed FastLED display
//  Serial.println(LEDS.getFPS()); 
//} // fastbracelet()


//void motion() {
//  
//  X = CircuitPlayground.motionX();
//  Y = CircuitPlayground.motionY();
//  Z = CircuitPlayground.motionZ();
// 
//   // Get the magnitude (length) of the 3 axis vector
//  // http://en.wikipedia.org/wiki/Euclidean_vector#Length
//  double storedVector = X*X;
//  storedVector += Y*Y;
//  storedVector += Z*Z;
//  storedVector = sqrt(storedVector);
//  Serial.print("Len: "); Serial.println(storedVector);
//  
//  // wait a bit
//  delay(100);
//  
//  // get new data!
//  X = CircuitPlayground.motionX();
//  Y = CircuitPlayground.motionY();
//  Z = CircuitPlayground.motionZ();
//  double newVector = X*X;
//  newVector += Y*Y;
//  newVector += Z*Z;
//  newVector = sqrt(newVector);
//  Serial.print("New Len: "); Serial.println(newVector);
//  
//  // are we moving 
//  if (abs(10*newVector - 10*storedVector) > MOVE_THRESHOLD) {
//    Serial.println("Twinkle!");
//    flashRandom(5, 1);  // first number is 'wait' delay, shorter num == shorter twinkle
//    flashRandom(5, 3);  // second number is how many neopixels to simultaneously light up
//    flashRandom(5, 2);
//  }
//}

//void flashRandom(int wait, uint8_t howmany) {
//
//  for(uint16_t i=0; i<howmany; i++) {
//    // pick a random favorite color!
//    int c = random(FAVCOLORS);
//    int red = myFavoriteColors[c][0];
//    int green = myFavoriteColors[c][1];
//    int blue = myFavoriteColors[c][2]; 
//
//    // get a random pixel from the list
//    int j = random(NUM_LEDS);
//    //Serial.print("Lighting up "); Serial.println(j); 
//    
//    // now we will 'fade' it in 5 steps
//    for (int x=0; x < 5; x++) {
//      int r = red * (x+1); r /= 5;
//      int g = green * (x+1); g /= 5;
//      int b = blue * (x+1); b /= 5;
//      
//      leds[j].r = r;
//      leds[j].g = g;
//      leds[j].b = b;
//      FastLED.show();
//      //CircuitPlayground.setPixelColor(j, r, g, b);
//      delay(wait);
//    }
//    // & fade out in 5 steps
//    for (int x=5; x >= 0; x--) {
//      int r = red * x; r /= 5;
//      int g = green * x; g /= 5;
//      int b = blue * x; b /= 5;
//
//      leds[j].r = r;
//      leds[j].g = g;
//      leds[j].b = b;
//      FastLED.show(); 
//      //CircuitPlayground.setPixelColor(j, r, g, b); 
//      delay(wait);
//    }
//  }
//  // LEDs will be off when done (they are faded to 0)
//}
