#include "FastLED.h"

// Matrix size
#define NUM_ROWS 8
#define NUM_COLS 8
#define BRIGHTNESS  30

// LEDs pin
#define DATA_PIN 3

#define NUM_LEDS NUM_ROWS * NUM_COLS

int LENGTH = 1;
CRGB colors[8] = {CRGB(255,0,0), CRGB(255,215,0), CRGB(255,153,0), CRGB(0,255,0), CRGB(0,0,255), CRGB(127,0,255) ,CRGB(255,0,255),CRGB(255,125,255)};


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
  //show the LEDs
  
}

void loop() {
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        leds[i + (j * 8)] = colors[j];
      }
      FastLED.show();
      delay(100);
      for (int j = 0; j < 8; j++){
        leds[i + (j * 8)] = CRGB::Black;
      }
    }
    for (int i = 7; i >= 0; i--){
      for (int j = 7; j >= 0; j--){
        leds[i + (j * 8)] = colors[j];
      }
      FastLED.show();
      delay(100);
      for (int j = 7; j >= 0; j--){
        leds[i + (j * 8)] = CRGB::Black;
      }
    }
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        leds[i + (j * 8)] = colors[7 - j];
      }
      FastLED.show();
      delay(100);
      for (int j = 0; j < 8; j++){
        leds[i + (j * 8)] = CRGB::Black;
      }
    }

        for (int i = 7; i >= 0; i--){
      for (int j = 7; j >= 0; j--){
        leds[i + (j * 8)] = colors[7 - j];
      }
      FastLED.show();
      delay(100);
      for (int j = 7; j >= 0; j--){
        leds[i + (j * 8)] = CRGB::Black;
      }
    }

    for (int i = 0; i < 64; i=i+8){
      for (int j = 0; j < 8; j++){
        leds[i + j] = colors[j];
      }
      FastLED.show();
      delay(100);
      for (int j = 0; j < 8; j++){
        leds[i + j] = CRGB::Black;
      }
    }

    for (int i = 63; i >= 0; i = i - 8){
      for (int j = 0; j < 8; j++){
        leds[i - j] = colors[7-j];
      }
      FastLED.show();
      delay(100);
      for (int j = 0; j < 8; j++){
        leds[i - j] = CRGB::Black;
      }
    }

    for (int i = 0; i < NUM_LEDS; i++){
      if (i >= 0 && i < 8){
        leds[i] = colors[0];
      }
       else if (i >= 8 && i < 16){
          leds[i] = colors[1];
       }
       else if (i >= 16 && i < 24){
          leds[i] = colors[2];
       }
       else if (i >= 24 && i < 32){
          leds[i] = colors[3];
       }
       else if (i >= 32 && i < 40){
          leds[i] = colors[4];
       }
       else if (i >= 40 && i < 48){
          leds[i] = colors[5];
       }
       else if (i >= 48 && i < 56){
          leds[i] = colors[6];
       }
       else if (i >= 56 && i < 64){
          leds[i] = colors[7];
       }
        FastLED.show();
    }

        for (int i = 0; i < NUM_LEDS; i++){
      if (i >= 0 && i < 8){
        leds[i] = colors[0];
      }
       else if (i >= 8 && i < 16){
          leds[i] = colors[1];
       }
       else if (i >= 16 && i < 24){
          leds[i] = colors[2];
       }
       else if (i >= 24 && i < 32){
          leds[i] = colors[3];
       }
       else if (i >= 32 && i < 40){
          leds[i] = colors[4];
       }
       else if (i >= 40 && i < 48){
          leds[i] = colors[5];
       }
       else if (i >= 48 && i < 56){
          leds[i] = colors[6];
       }
       else if (i >= 56 && i < 64){
          leds[i] = colors[7];
       }
        FastLED.show();
        FastLED.setBrightness(2);
    }
    for (int i = 0; i < NUM_LEDS; i++){
      if (i >= 0 && i < 8){
        leds[i] = colors[0];
      }
       else if (i >= 8 && i < 16){
          leds[i] = colors[1];
       }
       else if (i >= 16 && i < 24){
          leds[i] = colors[2];
       }
       else if (i >= 24 && i < 32){
          leds[i] = colors[3];
       }
       else if (i >= 32 && i < 40){
          leds[i] = colors[4];
       }
       else if (i >= 40 && i < 48){
          leds[i] = colors[5];
       }
       else if (i >= 48 && i < 56){
          leds[i] = colors[6];
       }
       else if (i >= 56 && i < 64){
          leds[i] = colors[7];
       }
        FastLED.show();
        
    }


}
