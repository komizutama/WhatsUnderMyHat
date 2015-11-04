#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define buttonPin 2
#define NUMPIXELS 24

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long interval = 1000;
unsigned long beatLength = 100;
unsigned long prevTime = 0;
unsigned long currenTime = 0;

int buttonState = 0;
boolean flashOn=true;
int stripColor;
uint16_t colorState= 0;


void setup() {
  //initialize pin 2 as switch input
  pinMode(buttonPin, INPUT);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    // turn ring green
    //makeColor(0, 256, 0);
    //rainbow(interval);
    rainbowCycle(25);
    //theaterChaseRainbow(interval);
    //randFullblink(interval);
    //rainFullblink(interval);
  }
  else {
  // turn ring DARK
  makeColor(0,0,0);
  }
}

void beatFlashPattern(uint8_t gap, uint8_t wait)
{
  
}


void makeColor(int r, int g, int b)
{
  for (uint16_t i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(r,g,b));
  }
  strip.show();
}  
 



//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 5; q++) 
    {
      currenTime = millis();
      if ((currenTime-prevTime) >= wait)
      {
        prevTime=currenTime;
        for (int i=0; i < strip.numPixels(); i=i+3) 
        {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();

      for (int i=0; i < strip.numPixels(); i=i+5) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
    }
  }
}

void randColor()
{
  int newStripColor = stripColor;
  while (abs(newStripColor-stripColor) < 2)
  {
    newStripColor = Wheel(random(10,256));
  }
  stripColor = newStripColor;
}
void randFullblink(uint8_t wait){
  currenTime = millis();
  if ((currenTime-prevTime) >= wait){
    prevTime=currenTime;
    stripColor=Wheel(random(256));//generate random color
    for (uint16_t i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, stripColor);
    }
  strip.show();
}
}

void rainFullblink(uint8_t wait){
  currenTime = millis();
  if ((currenTime-prevTime) >= wait){
    prevTime=currenTime;
    for (int j=0; j < 256; j++){
    stripColor=Wheel(j);
    for (uint16_t i=0; i<strip.numPixels(); i++)
    {
      strip.setPixelColor(i, stripColor);
    }
  strip.show();
  
}
}

}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  
  
  for(j=0; j<256; j++) {
    currenTime = millis();
    if ((currenTime-prevTime) >= wait){
    prevTime=currenTime;
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
  }
}
}
 

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i;
  
  currenTime = millis();
  if ((currenTime-prevTime) >= wait)
  {
    colorState+=10;
    prevTime=currenTime;
    for(i=0; i< strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, Wheel(((i * 255 / strip.numPixels()) + colorState) & 255));
    }
    strip.show();
  }

}

/*
void rainbowCycleFlash(uint8_t wait, uint8_t gapFlash) {
  uint16_t i, j;

  for(j=0; j<256; j++) 
  {
    currenTime = millis();
    if ((currenTime-prevTime) >= gapFlash)
    {
      for(i=0; i< strip.numPixels(); i++) 
      {
        strip.setPixelColor(i, Wheel(((i * 255 / strip.numPixels()) + j) & 255));
      }
      strip.show();
    }
    else if ((currenTime-prevTime) >= wait){
      prevTime=currenTime;
      for(i=0; i< strip.numPixels(); i++) 
      {
        strip.setPixelColor(i,strip.Color(255,255,255)));
      }
      strip.show();
}
}
}
*/

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.



uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

