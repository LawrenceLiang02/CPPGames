#include "FastLED.h"

// Matrix Info
const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const int BRIGHTNESS = 5;
const int NUM_LEDS = NUM_ROWS * NUM_COLS;

// Pins
const int DATA_PIN = 3;
const int switch1 = A0;
const int switch2 = A1;
const int switch3 = A2;
const int switch4 = A3;
const int startSwitch = A4;

// Array of colors
CRGB colors[4] = {CRGB(255,0,0), CRGB(0,0,255), CRGB(255,0,255), CRGB(0,255,0)};

// Settings
const int sequenceSize = 100;
const int minVelocity = 2000;
const int maxVelocity = 1000;

// Define the array of leds
CRGB leds[NUM_LEDS];

// Other Attributes
bool canContinue = false;
bool canReadNext = false;
bool success = true;
unsigned long expectedEndTime;

int sequence[sequenceSize];
int inputSequence[sequenceSize];

int velocity;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

void loop() {
  reset_leds();

  if (digitalRead(startSwitch) == LOW && canContinue == false)
  {
    generate_sequence();
    canContinue = true;    
    Serial.println("Start");
    show_sequence();
  }
  
}

void generate_sequence()
{
  randomSeed(millis());

  for (int i = 0; i < sequenceSize; i++)
  {
    sequence[i] = random(1,5);
  }
}

void show_sequence(){
  velocity = minVelocity;
  for (int seqPos = 0; seqPos < sequenceSize; seqPos++){
      reset_leds();

    if (canContinue){
      int bigrow1 = seqPos;
      int row1 = (sequence[bigrow1] * 2) -1;
      int row2 = (sequence[bigrow1] * 2) -2;
      leds[row1] = colors[sequence[bigrow1]-1];
      leds[row2] = colors[sequence[bigrow1]-1];
      leds[row1 + 8 * 1] = colors[sequence[bigrow1]-1];
      leds[row2 + 8 * 1] = colors[sequence[bigrow1]-1];
      
      int bigrow2 = seqPos + 1;
      if (bigrow2 < sequenceSize){
          int row3 = (sequence[bigrow2] * 2) -1;
          int row4 = (sequence[bigrow2] * 2) -2;
          leds[row3 + 8 * 2] = colors[sequence[bigrow2]-1];
          leds[row4 + 8 * 2] = colors[sequence[bigrow2]-1];
          leds[row3 + 8 * 3] = colors[sequence[bigrow2]-1];
          leds[row4 + 8 * 3] = colors[sequence[bigrow2]-1]; 
      }
  
  
      int bigrow3 = seqPos + 2;
      if (bigrow3 < sequenceSize){
        int row5 = (sequence[bigrow3] * 2) -1;
        int row6 = (sequence[bigrow3] * 2) -2;
        leds[row5 + 8 * 4] = colors[sequence[bigrow3]-1];
        leds[row6 + 8 * 4] = colors[sequence[bigrow3]-1];
        leds[row5 + 8 * 5] = colors[sequence[bigrow3]-1];
        leds[row6 + 8 * 5] = colors[sequence[bigrow3]-1];
      }
      
      int bigrow4 = seqPos + 3;
      if (bigrow4 < sequenceSize){
        int row7 = (sequence[bigrow4] * 2) -1;
        int row8 = (sequence[bigrow4] * 2) -2;
        leds[row7 + 8 * 6] = colors[sequence[bigrow4]-1];
        leds[row8 + 8 * 6] = colors[sequence[bigrow4]-1];
        leds[row7 + 8 * 7] = colors[sequence[bigrow4]-1];
        leds[row8 + 8 * 7] = colors[sequence[bigrow4]-1];
      }
      canReadNext = true;
      FastLED.show();
      Serial.print("Expected Button: ");
      Serial.println(sequence[seqPos]);
      expectedEndTime = millis() + velocity;
      while(expectedEndTime > millis()&& canReadNext == true){
        if (digitalRead(switch1) == LOW){
          inputSequence[seqPos] = 1;
          canReadNext = false;
          delay(100);
        }
        else if (digitalRead(switch2) == LOW){
          inputSequence[seqPos] = 2;
          canReadNext = false;
          delay(100);
        }
        else if (digitalRead(switch3) == LOW){
          inputSequence[seqPos] = 3;
          canReadNext = false;
          delay(100);
        }
        else if (digitalRead(switch4) == LOW){
          inputSequence[seqPos] = 4;
          canReadNext = false;
          delay(100);
        }
      
      }
      Serial.print("Actual Button: ");
      Serial.println(inputSequence[seqPos]);
      if (canReadNext == true){
        canContinue = false;
        wrong_sequence();
        Serial.println("Expired");
        success = false;
        break;
      }
       
      if (sequence[seqPos] != inputSequence[seqPos]){
        canContinue = false;
        wrong_sequence();
        Serial.println("Wrong Input");
        success = false;
        break;
      }
      
      if (velocity > maxVelocity){
        velocity -= 25;
        Serial.print("Velocity: ");
        Serial.println(velocity);
      }
      success = true;
    }
    
  }
  if (success){
    right_sequence();
  }
  canContinue = false;
}

void reset_leds(){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}

void wrong_sequence(){
  reset_leds();
   for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  for (int i = 0; i < NUM_LEDS; i = i + 9){
    leds[i] = CRGB(255,0,0);
    leds[i + 1] = CRGB(255,0,0);
    leds[i - 1] = CRGB(255,0,0);
  }

  for (int i = 7; i < NUM_LEDS; i = i + 7){
    leds[i] = CRGB(255,0,0);
    leds[i+1] = CRGB(255,0,0);
    leds[i - 1] = CRGB(255,0,0);
  }
  FastLED.show();
  delay(2000);
}

void right_sequence(){
   reset_leds();
   for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,255,0);
  }
  FastLED.show();
  delay(2000);
}
