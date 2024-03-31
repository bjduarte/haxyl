// WS2811 test program.
// Turns output on and off (0% to 100% duty cycle).
// Drives motors with short reverse-voltage pulse to rapidly spin them down.

#include <FastLED.h>
#include <Ramp.h>
#include <string>

#define NUM_LEDS 5
#define DATA_PIN 6
#define REVERSING_TIME 40
#define RUN_TIME 5000
#define HIGH_VALUE 200
#define LIGHT_VALUE 255
#define STAGES 10
#define TIME_BETWEEN 50

CRGB leds[NUM_LEDS];
rampInt myramp;

char receivedChar = '\0';
boolean newData = false;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
  myramp.go(200);
  myramp.update();
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChar);
        newData = false;
    }
}

void on_pattern(int arr[]){
  int sz = NUM_LEDS;
  for(int j = 0; j < STAGES; j ++){
    int stage = myramp.update(); // HIGH_VALUE - HIGH_VALUE / STAGES * j;

    Serial.println(stage);

    int d = RUN_TIME / STAGES;// myramp.update();//(RUN_TIME / (1 + STAGES) * (j + 1)) / (STAGES);//(RUN_TIME / (1 + STAGES) + j * RUN_TIME / STAGES) / 2;

    // Serial.println(d);

    for(int i = 0; i < sz; i ++){
      int idx = arr[i];
      // Set H-bridge to forward mode:
      leds[idx].green = 0;
      // Set forward power to 100%:
      leds[idx].red = stage;
      // Light up on-board LED at 100% brightness:
      leds[idx].blue = LIGHT_VALUE;
    }

    // Send frame to WS2811 chips:
    FastLED.show();

    // Wait while motors run:
    delay(d);
  }
}

void haxil_on(int arr[]){
  on_pattern(arr);

  int sz = NUM_LEDS;

  for(int i = 0; i < sz; i ++){
    int idx = arr[i];
    // Set reverse power to 100%:
    leds[idx].green = 255;
    // Set H-bridge to reverse mode:
    leds[idx].red = 0;
    // Turn off on-board LED:
    leds[idx].blue = 0;
  }

  // Send frame to WS2811 chips:
  FastLED.show();

  Serial.println("Reversing");

  // Wait for spin-down:
  delay(REVERSING_TIME);

  // Serial.println(sz);

  for(int i = 0; i < sz; i ++){
    int idx = arr[i];
    // Set H-bridge to forward mode:
    leds[idx].green = 0;
    // Set forward power to 0%:
    leds[idx].red = 0;
    // Turn off on-board LED:
    leds[idx].blue = 0;
  }

  // Send frame to WS2811 chips:
  FastLED.show();

  // Wait for next cycle:
  delay(TIME_BETWEEN);
  myramp.go(200);
  myramp.update();
}

void loop() {
  // Spin up 3 motors in string:
  // Serial.println(Serial.available());
  //for now only receive one character and display it
  recvOneChar();
  showNewData();
  int data = receivedChar - 97;
  if((data >= 0) && (data < 26)){
    Serial.println(data);
    myramp.go(50, 5000, EXPONENTIAL_OUT);
    int arr[] = {0, 1, 2, 3, 4};
    haxil_on(arr);
    receivedChar = '\0';
  }
}