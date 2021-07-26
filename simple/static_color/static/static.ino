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
  
    for (int i=0; i<NUMPIXELS; i++) {
      strip.setPixelColor(i, 255, 0, 0); // Set all pixels to bright red
    }
    strip.show();
  while (true) {} // loop forever
}
