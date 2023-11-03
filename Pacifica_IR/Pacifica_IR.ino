#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Define the pin connected to the data input of your LED strip
#define NUM_LEDS 60     // Define the number of LEDs in your strip
#define MAX_BRIGHTNESS 255  // Maximum brightness (0-255)
#define BRIGHTNESS_STEP 10   // Small step for gradual increase
#define BRIGHTNESS_INTERVAL 10  // Interval in milliseconds between steps
#define PERIOD 2000      // Duration of one complete cycle in milliseconds (2 seconds)
#define LED_FADE 1000    // Duration of the fade in/out portion of the cycle (1 second)

int brightness = 128;  // Initial brightness level
bool increasingBrightness = true; // Flag to control brightness change
unsigned long previousMillis = 0;

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

void setup() {
  delay(1000);
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready");

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
}

// void gradualChangeBrightness(bool increase) {
//   int targetBrightness = increase ? MAX_BRIGHTNESS : 0;
//   for (int currentBrightness = FastLED.getBrightness(); currentBrightness != targetBrightness; currentBrightness += (increase ? BRIGHTNESS_STEP : -BRIGHTNESS_STEP)) {
//     FastLED.setBrightness(currentBrightness);
//     FastLED.show();
//     delay(BRIGHTNESS_INTERVAL);
//   }
// }

// void gradualChangeBrightness() {
//   int targetBrightness = increasingBrightness ? MAX_BRIGHTNESS : 0;
//   for (int currentBrightness = brightness; currentBrightness != targetBrightness; currentBrightness += (increasingBrightness ? BRIGHTNESS_STEP : -BRIGHTNESS_STEP)) {
//     FastLED.setBrightness(currentBrightness);
//     FastLED.show();
//     delay(BRIGHTNESS_INTERVAL);
//   }
//   increasingBrightness = !increasingBrightness;
// }

void gradualBrightnessChange() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= PERIOD) {
    previousMillis = currentMillis;
    increasingBrightness = !increasingBrightness; // Invert the direction of change
  }

  if (currentMillis - previousMillis <= LED_FADE) {
    if (increasingBrightness) {
      if (brightness < MAX_BRIGHTNESS) {
        brightness++;
      }
    } else {
      if (brightness > 0) {
        brightness--;
      }
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
  }
}

void loop() {

  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.command);

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
        gradualBrightnessChange();
        break;

      case hash:
        fill_rainbow(leds, NUM_LEDS, 0, 7);
        break;

    }
    FastLED.show();
    IrReceiver.resume();

  }
}
