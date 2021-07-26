// Import the Adafruit Neopixel library
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals.
// Which pin on the ESP32 is connected to the NeoPixels?
#define PIN        12 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 40// Popular NeoPixel ring size

// Initialize Neopixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

/* setup function */
void setup(void) {
  strip.begin();
  strip.setBrightness(40); // Set LEDs to ~1/6 brightness
}

// Own routines
void loop(void) {
  // Own program code
  while (true) {
    for (int j=0; j<16; j++) {
      if (j%4<2) {
        // Sides looping through forward
        for (int p=0; p<NUMPIXELS; p++) {
          strip.clear();
          for (int i=0; i<11; i++) {
            strip.setPixelColor((i+p)%40, 255, 0, 0);
          }
          for (int i=11; i<20; i++) {
            strip.setPixelColor((i+p)%40, 0, 255, 0);
          }
          for (int i=20; i<31; i++) {
            strip.setPixelColor((i+p)%40, 0, 0, 255);
          }
          for (int i=31; i<40; i++) {
            strip.setPixelColor((i+p)%40, 255, 255, 0);
          }
          strip.show();
          delay(30);
        }
        } else {
      // Sides looping through backward
        for (int p=0; p<NUMPIXELS; p++) {
          strip.clear();
          for (int i=0; i<11; i++) {
            strip.setPixelColor(NUMPIXELS-(i+p)%40, 255, 0, 0);
          }
          for (int i=11; i<20; i++) {
            strip.setPixelColor(NUMPIXELS-(i+p)%40, 0, 255, 0);
          }
          for (int i=20; i<31; i++) {
            strip.setPixelColor(NUMPIXELS-(i+p)%40, 0, 0, 255);
          }
          for (int i=31; i<40; i++) {
            strip.setPixelColor(NUMPIXELS-(i+p)%40, 255, 255, 0);
          }
          strip.show();
          delay(30);
        }
      }
    }
  } // loop forever
}
