// WS2811 test program.
// Turns output on and off (0% to 100% duty cycle).
// Drives motors with short reverse-voltage pulse to rapidly spin them down.

#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 6
#define REVERSING_TIME 40
#define RUN_TIME 1000

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Spin up all motors in string:
  for(int i = 0; i < NUM_LEDS; i++)
  {
    // Set H-bridge to forward mode:
    leds[i].green = 0;

    // Set forward power to 100%:
    leds[i].red = 255;

    // Light up on-board LED at 100% brightness:
    leds[i].blue = 255;

    // Send frame to WS2811 chips:
    FastLED.show();
  }
  
  // Wait while motors run:
  delay(RUN_TIME);

  // Apply reverse torque to all motors in string:
  for(int i = 0; i < NUM_LEDS; i++)
  {
    // Set reverse power to 100%:
    leds[i].green = 255;

    // Set H-bridge to reverse mode:
    leds[i].red = 0;

    // Turn off on-board LED:
    leds[i].blue = 0;

    // Send frame to WS2811 chips:
    FastLED.show();
  }

  // Wait for spin-down:
  delay(REVERSING_TIME);

  // Turn off all motors in string:
  for(int i = 0; i < NUM_LEDS; i++)
  {
    // Set H-bridge to forward mode:
    leds[i].green = 0;

    // Set forward power to 0%:
    leds[i].red = 0;

    // Turn off on-board LED:
    leds[i].blue = 0;

    // Send frame to WS2811 chips:
    FastLED.show();
  }
  
  // Wait for next cycle:
  delay(RUN_TIME);

}
