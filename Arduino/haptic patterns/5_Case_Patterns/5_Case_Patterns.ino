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
char[] message;
int msgIdx = 0;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(115200);
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

/* This section is comprised of functions which affect a single motor */

void on_one(int idx, int intensity){
  // Set H-bridge to forward mode:
  leds[idx].green = 0;
  // Set forward power to 100%:
  leds[idx].red = intensity;
  // Light up on-board LED at 100% brightness:
  leds[idx].blue = LIGHT_VALUE;
}

void reverse_one(int idx){
  // Set reverse power to 100%:
  leds[idx].green = 255;
  // Set H-bridge to reverse mode:
  leds[idx].red = 0;
  // Turn off on-board LED:
  leds[idx].blue = 0;
}

void off_one(int idx){
  // Set H-bridge to forward mode:
  leds[idx].green = 0;
  // Set forward power to 0%:
  leds[idx].red = 0;
  // Turn off on-board LED:
  leds[idx].blue = 0;
}

/* This section is comprised of functions which use the single-motor functions to implement patterns */

//currently sets all of the leds to "ramp down"
void pattern1(int arr[], int size){
  for(int j = 0; j < STAGES; j ++){
    int stage = myramp.update(); // HIGH_VALUE - HIGH_VALUE / STAGES * j;

    Serial.println(stage);

    int d = RUN_TIME / STAGES;

    for(int i = 0; i < size; i ++){
      int idx = arr[i];
      on_one(idx, stage);
    }

    // Send frame to WS2811 chips:
    FastLED.show();

    // Wait while motors run:
    delay(d);
  }
}

//makes them go one at a time at max-ish speed
void pattern2(int arr[], int size){
  for(int j = 0; j < size; j ++){
    int d = RUN_TIME / size;
    int idx = arr[j];
    on_one(idx, HIGH_VALUE);

    // Send frame to WS2811 chips:
    FastLED.show();

    // Wait while motors run:
    delay(d);

    // Turn that motor off:
    reverse_one(idx);
    FastLed.show();
    delay(REVERSING_TIME);
    off_one(idx);
    FastLed.show();
  }
}

void pattern3(int arr[], int size){
  for(int i = 0; i < size; i ++){
    
  }
}

void turn_all_off(int arr[], int size){
  // Reverse each LED in the array:
  for(int i = 0; i < size; i ++){
    int idx = arr[i];
    reverse_one(idx);
  }
  // Send frame to WS2811 chips:
  FastLED.show();
  Serial.println("Reversing");
  // Wait for spin-down:
  delay(REVERSING_TIME);

  // Turn each LED off:
  for(int i = 0; i < size; i ++){
    int idx = arr[i];
    off_one(idx)
  }
  // Send frame to WS2811 chips:
  FastLED.show();
  // Wait for next cycle:
  delay(TIME_BETWEEN);
}

void haxil_on(int arr[], size, int state){
  // Pattern for going down a lot is a large ramp function starting at 200
  if(state == -2){
    myramp.go(200);
    myramp.update();
    pattern1(arr, size);
    turn_all_off(arr, size);
  }
  // Pattern for going down a little is a small ramp function starting at 125
  if(state == -1){
    myramp.go(125);
    myramp.update();
    pattern1(arr, size);
    turn_all_off(arr, size);
  }
  // Pattern for going up a little is a one at a time turning one motor on to 200
  if(state == 1){
    pattern2(arr, size);
    turn_all_off(arr, size);
  }
  // Pattern for going up a lot is all of the motors at once turning on to 200
  if(state == 2){
    pattern3(arr, size);
    turn_all_off(arr, size);
  }
}

void loop() {
  //for now only receive one character and display it
  recvOneChar();
  showNewData();
  int data = receivedChar - 97;
  if((data >= 0) && (data < 26)){
    Serial.println(data);
    myramp.go(50, 5000, EXPONENTIAL_OUT);
    int arr[] = {0, 1, 2, 3, 4};
    haxil_on(arr, 5, data);
    receivedChar = '\0';
  }
}