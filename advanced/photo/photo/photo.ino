/* Photo lithophane example by3D Printing Geek 
   YouTube: https://www.youtube.com/channel/UCT4x1kFmJFZWkokIamnbFCA
   Twitter: https://mobile.twitter.com/PrintingGeek
*/   

// Change definitions for used pin, number of NeoPixels 
// and matrix size in configuration.h to the ones you need.
#include "configuration.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Simple gamma correction for Neopixels
const uint8_t PROGMEM gamma8[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};

// LED matrix 16x7 pixel RGB values
// Every 2nd row reversed because of led matrix is reversed every 2nd row
int colors[][3] = {{ 255, 235, 193},
  { 64, 64, 255},
  { 150, 150, 255},
  { 64, 64, 255},
  { 128, 128, 255},
  { 64, 64, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255,  150, 150},
  { 255,  150, 150},
  { 255,  150, 150},
  { 255, 128, 128},
  { 255, 255, 255},

  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 235, 193},
  { 255, 235, 193},

  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},

  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 247, 144},
  { 255, 247, 144},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},
  { 255, 235, 193},

  { 0, 255, 0},
  { 255, 235, 193},
  { 255, 255, 255},
  { 255, 247, 144},
  { 255, 247, 144},
  { 255, 255, 255},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 150, 150, 150},
  { 150, 150, 150},

  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 255, 255, 255},
  { 150, 150, 150},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 182, 182},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 0, 255, 0},
  { 0, 255, 0},

  { 255,  150, 150},
  { 255, 182, 182},
  { 255, 182, 182},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 255, 255, 255},
  { 150, 150, 150},
  { 150, 150, 150},
  { 150, 150, 150},
  { 0, 0, 0}
};

int led_shown = false;


/* setup function */
void setup(void) {
  strip.begin();
  strip.setBrightness(40); // 1/6 brightness

}

// Own routines
// Populate leds with colors for photo
void color_photo() {
  for (int j = 0; j < LED_COLS; j++) {
    for (int k = 0; k < LED_ROWS; k++) {
      strip.setPixelColor(j * LED_ROWS + k, pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][0]]),
                          pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][1]]),
                          pgm_read_byte(&gamma8[colors[j * LED_ROWS + k][2]]));
    }
  }
  strip.show();
  led_shown = true;
}

// This produces a nice rainbow effect 
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i * 1 + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
 // Main loop
void loop(void) {
  if (!led_shown) {
    color_photo();
    // rainbow(200);  // comment above line and uncomment this for rainbow effect
    led_shown = true;
  }
}
