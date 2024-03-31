// WS2811 test program.
// Turns output on and off (0% to 100% duty cycle).
// Drives motors with short reverse-voltage pulse to rapidly spin them down.

#include <FastLED.h>

#define NUM_LEDS 5
#define DATA_PIN 6
#define REVERSING_TIME 40
#define RUN_TIME 5000
#define HIGH_VALUE 200
#define LIGHT_VALUE 255
#define STAGES 10
#define TIME_BETWEEN 50

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  // Spin up all motors in string:
  for(int i = 0; i < NUM_LEDS; i++)
  {
    for(int j = 0; j < STAGES; j ++){
      int stage = HIGH_VALUE / STAGES * j;

      Serial.println(stage);

      int d = RUN_TIME / STAGES;

      Serial.println(d);

      // Set H-bridge to forward mode:
      leds[i].green = 0;

      // Set forward power to 100%:
      leds[i].red = stage;

      // Light up on-board LED at 100% brightness:
      leds[i].blue = LIGHT_VALUE;

      // Send frame to WS2811 chips:
      FastLED.show();

      // Wait while motors run:
      delay(d);
    }

    // Set reverse power to 100%:
    leds[i].green = 255;

    // Set H-bridge to reverse mode:
    leds[i].red = 0;

    // Turn off on-board LED:
    leds[i].blue = 0;

    // Send frame to WS2811 chips:
    FastLED.show();

    Serial.println("Reversing");

    // Wait for spin-down:
    delay(REVERSING_TIME);

    // Set H-bridge to forward mode:
    leds[i].green = 0;

    // Set forward power to 0%:
    leds[i].red = 0;

    // Turn off on-board LED:
    leds[i].blue = 0;

    // Send frame to WS2811 chips:
    FastLED.show();

    // Wait for next cycle:
    delay(TIME_BETWEEN);
  }
}
