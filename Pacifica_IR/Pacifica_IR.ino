#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Define the pin connected to the data input of your LED strip
#define NUM_LEDS 60     // Define the number of LEDs in your strip
#define MAX_BRIGHTNESS 255  // Maximum brightness (0-255)
#define BRIGHTNESS_STEP 10   // Small step for gradual increase
#define BRIGHTNESS_INTERVAL 10  // Interval in milliseconds between steps
#define FADE_STEP 1

int brightness = 128;  // Initial brightness level

// Common CRGB colors
CRGB red = CRGB(255, 0, 0);
CRGB green = CRGB(0, 255, 0);
CRGB blue = CRGB(0, 0, 255);
CRGB white = CRGB(255, 255, 255);
CRGB black = CRGB(0, 0, 0);
CRGB yellow = CRGB(255, 255, 0);
CRGB magenta = CRGB(255, 0, 255);
CRGB cyan = CRGB(0, 255, 255);
CRGB orange = CRGB(255, 165, 0);
CRGB pink = CRGB(255, 192, 203);
CRGB purple = CRGB(128, 0, 128);
CRGB teal = CRGB(0, 128, 128);
CRGB violet = CRGB(238, 130, 238);
CRGB lavender = CRGB(230, 230, 250);
CRGB indigo = CRGB(75, 0, 130);
CRGB brown = CRGB(139, 69, 19);

// IR BUTTON CODES
const int zero = 25;
const int one = 69;
const int two = 70;
const int three = 71;
const int four = 68;
const int five = 64;
const int six = 67;
const int seven = 7;
const int eight = 21;
const int nine = 9;
const int star = 22;
const int up = 24;
const int down = 82; 
const int ok = 28;
const int hash = 13;

const int IR_PIN = 0;  // Define the digital pin where the IR receiver is connected
IRrecv irrecv(IR_PIN);
decode_results results;

CRGB leds[NUM_LEDS];


//
bool runWhileTrueLoop = false;  // A flag to control the while(true) loop

unsigned long task1PreviousMillis = 0;
const unsigned long task1Interval = 1000;  // Task 1 interval in milliseconds

unsigned long task2PreviousMillis = 0;
const unsigned long task2Interval = 500;  // Task 2 interval in milliseconds

const unsigned long interval = 500;
unsigned long previousTime = 0;
//


void setup() {
  delay(1000);
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

void gradualIncreaseBrightness() {
  while (brightness < MAX_BRIGHTNESS) {
    brightness += FADE_STEP;
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(BRIGHTNESS_INTERVAL);
  }
}

void gradualDecreaseBrightness() {
  while (brightness > 50) {
    brightness -= FADE_STEP;
    FastLED.setBrightness(brightness);
    FastLED.show();
    delay(BRIGHTNESS_INTERVAL);
  }
}


void loop() {
  unsigned long currentMillis = millis();

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);

    // // Check a condition to start or stop the while(true) loop
    // if (IrReceiver.decodedIRData.command != ok) {
    //   runWhileTrueLoop = false;
    //   Serial.println("runWhileTrueLoop = false");
    // }

    // Task 1: Execute every task1Interval milliseconds
    if (currentMillis - task1PreviousMillis >= task1Interval) {
      task1PreviousMillis = currentMillis;
      // Task 1 code here
      // if (IrReceiver.decodedIRData.command != ok) {
      //   Serial.println("TEST!!!");
      //   exitLoop = true;
      // }
          // Check a condition to start or stop the while(true) loop
      if (IrReceiver.decodedIRData.command != ok) {
        runWhileTrueLoop = false;
        Serial.println("runWhileTrueLoop = false");
      }
    }

    switch (IrReceiver.decodedIRData.command) {
      case one:
        fill_solid(leds, NUM_LEDS, red);
        break;

      case two:
        fill_solid(leds, NUM_LEDS, green);
        break;

      case three:
        fill_solid(leds, NUM_LEDS, blue);
        break;

      case four:
        fill_solid(leds, NUM_LEDS, yellow);
        break;

      case five:
        fill_solid(leds, NUM_LEDS, orange);
        break;

      case six:
        fill_solid(leds, NUM_LEDS, violet);
        break;

      case star:
        fill_solid(leds, NUM_LEDS, black);
        break;

      case up:
        if (brightness + BRIGHTNESS_STEP <= MAX_BRIGHTNESS) {
          brightness += BRIGHTNESS_STEP;
          FastLED.setBrightness(brightness);
        }
        break;

      case down:
        if (brightness - BRIGHTNESS_STEP >= 0) {
          brightness -= BRIGHTNESS_STEP;
          FastLED.setBrightness(brightness);
        }
        break;

      case ok:
        runWhileTrueLoop = true;
        Serial.println("runWhileTrueLoop = true");
        if (runWhileTrueLoop) {
          // Independent while(true) loop
          while (true) {
            // Code for the independent loop

            // Use millis() for timing within the loop
            unsigned long currentTime = millis();
            // Perform actions based on timing or conditions
            if (currentTime - previousTime >= interval) {
              // Perform some action
              gradualIncreaseBrightness();
              gradualDecreaseBrightness();
              previousTime = currentTime;  // Update previousTime
            }

            // Break out of the while(true) loop when needed
            if (!runWhileTrueLoop) {
              break;
            }
          }
        }



        // while (!exitLoop){
        //   gradualIncreaseBrightness();
        //   gradualDecreaseBrightness();
        //   delay(1000);
        // }

        break;

      case hash:
        fill_rainbow(leds, NUM_LEDS, 0, 7);
        break;

    }
    FastLED.show();
    IrReceiver.resume();

  }
}
