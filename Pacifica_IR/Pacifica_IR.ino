#include <IRremote.h>
#include <FastLED.h>

#define LED_PIN 3       // Define the pin connected to the data input of your LED strip
#define NUM_LEDS 60     // Define the number of LEDs in your strip
#define BRIGHTNESS 64   // Set the brightness (0-255)

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
  FastLED.setBrightness(BRIGHTNESS);
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

    }
    FastLED.show();
    IrReceiver.resume();

  }
}
