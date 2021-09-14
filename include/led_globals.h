///////////////////////////////////////////////////////////////////////////////////////////
//                    RGB LEDs                                                           //
///////////////////////////////////////////////////////////////////////////////////////////
#include <FastLED.h>
//
// Global Variables
//
int hue = 0;
uint32 led_last;
#define NUM_LEDS 8
#define DATA_PIN 15
CRGB leds[NUM_LEDS];
int led_brightness = 64;

void LED_Setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(led_brightness);
}

void example_show_LED()
{
  CHSV color = CHSV(60, 255, 255);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}