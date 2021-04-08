#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN        2
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pixels.begin();
}

void loop() {
  pixels.clear();
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      int r = random(0,255);
      int g = random(0,255);
      int b = random(0,255);
      int brightness = random(0,255);
      //pixels.setBrightness(brightness);
      pixels.fill(pixels.Color(r,g,b), i, 10);
      //pixels.setPixelColor(i, pixels.Color(r,g,b)); // Draw new pixel
      Serial.println(i);
      pixels.show();
      delay(50);
      pixels.setPixelColor(i, 0);
  }
}
