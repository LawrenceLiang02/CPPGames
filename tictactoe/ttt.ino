#include "FastLED.h"
#include <IRremote.h>

// Matrix Info
const int NUM_ROWS = 8;
const int NUM_COLS = 8;
const int BRIGHTNESS = 5;
const int NUM_LEDS = NUM_ROWS * NUM_COLS;

// Pins
const int REMOTE_PIN = 2;
const int DATA_PIN = 4;

//Colors
CRGB gridColor = CRGB(255,255,255);
CRGB playerColors[2] = {CRGB(255,0,0), CRGB(0,0,255)};

// Define the array of leds and IR Remote
CRGB leds[NUM_LEDS];
IRrecv irrecv(REMOTE_PIN);
decode_results results;

//Set Up
int currentLocation;
int currentPlayer;
bool gameStarted = false;
int playerOneSelection[5] = {};
int playerTwoSelection[5]  = {};
int playerOneArraySize = 0;
int playerTwoArraySize = 0;
bool repeatCheck;

//Square Information
const int SQ_HEIGHT = 2;
const int SQ_WIDTH = 2;
const int SQ_NUM = SQ_HEIGHT * SQ_WIDTH;

int squares[9][SQ_NUM]{
  {0,1,8,9},
  {3,4,11,12},
  {6,7,14,15},
  {24,25,32,33},
  {27,28,35,36},
  {30,31,38,39},
  {48,49,56,57},
  {51,52,59,60},
  {54,55,62,63}
};

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  irrecv.enableIRIn();
}


void loop() {
  if(irrecv.decode(&results)) {
    if(results.value == 0xFF02FD && gameStarted == false){ //RED BUTTON
      gameStarted = true;
      currentPlayer = 1;
      currentLocation = 5;
      playerOneArraySize = 0;
      playerTwoArraySize = 0;
      for (int i = 0; i < 5; i++){
        playerOneSelection[i] = 0;
        playerTwoSelection[i] = 0;
      }
      displaySelection(currentLocation, currentPlayer);
      displayGrid();
      selection();
    }
  }
}

void displayGrid(){
  for (int i = (8 * 2); i < (8 * 3); i++){
    leds[i] = gridColor;
  }
  for (int i = (8 * 5); i < (8 * 6); i++){
    leds[i] = gridColor;
  }
  for (int i = 2; i < NUM_LEDS; i = i + NUM_COLS){
    leds[i] = gridColor;
  }
  for (int i = 5; i < NUM_LEDS; i = i + NUM_COLS){
    leds[i] = gridColor;
  }
  FastLED.show();
}

void selection(){
  while (gameStarted){
    irrecv.resume();
    if(irrecv.decode(&results)) {
      switch(results.value) {
      case 0xFF629D:  // UP KEY
        currentLocation -= 3;
        borderLimitCheck();
        displaySelection(currentLocation, currentPlayer);
        break;
      case 0xFF22DD:  // LEFT KEY
        currentLocation -= 1;
        borderLimitCheck();
        displaySelection(currentLocation, currentPlayer);
        break;
      case 0xFFC23D:  // RIGHT KEY
        currentLocation += 1;
        borderLimitCheck();
        displaySelection(currentLocation, currentPlayer);
        break;
      case 0xFFA857:  // DOWN KEY
        currentLocation += 3;
        borderLimitCheck();
        displaySelection(currentLocation, currentPlayer);
        break;
      case 0xFF02FD: //RED BUTTON
        selectSquare(currentLocation, currentPlayer);
        break;
      default:
        irrecv.resume();
        break;
      }
      if (gameStarted){
        displaySelected();
      }
      
    }

  }

}

void displaySelection(int location, int player){
  resetLeds();
  for (int j = 0; j < SQ_NUM; j++){
    leds[squares[location-1][j]] = playerColors[player-1];
  }
  displayGrid();
  FastLED.show();
}

void borderLimitCheck(){
  if (currentLocation > 9){
    currentLocation -= 9;
  }
  else if(currentLocation <= 0){
    currentLocation += 9;
  }
  findNextAvailable();

}

void selectSquare(int location, int player){
  for (int j = 0; j < SQ_NUM; j++){
    leds[squares[location-1][j]] = CRGB(0,0,0);
  }
  FastLED.show();
  delay(500);
  for (int j = 0; j < SQ_NUM; j++){
    leds[squares[location-1][j]] = playerColors[player-1];
  }
  FastLED.show();
  delay(500);
  for (int j = 0; j < SQ_NUM; j++){
    leds[squares[location-1][j]] = CRGB(0,0,0);
  }
  FastLED.show();
  delay(500);
  
  for (int j = 0; j < SQ_NUM; j++){
    leds[squares[location-1][j]] = playerColors[player-1];
  }
  FastLED.show();
  if (player == 1){
    playerOneSelection[playerOneArraySize] = location;
    playerOneArraySize += 1;
    checkWin(currentPlayer);
    currentPlayer = 2;
  }
  else if (player == 2){
    playerTwoSelection[playerTwoArraySize] = location;
    playerTwoArraySize += 1;
    checkWin(currentPlayer);
    currentPlayer = 1;
  }
  if (gameStarted){
     findNextAvailable();

     displaySelection(currentLocation, currentPlayer);
  }

}

void displaySelected(){
  for (int i = 0; i < playerOneArraySize; i++){
    for (int j = 0; j < SQ_NUM; j++){
      leds[squares[playerOneSelection[i] -1][j]] = playerColors[0];
    }
    
  }

  for (int i = 0; i < playerTwoArraySize; i++){
    for (int j = 0; j < SQ_NUM; j++){
      leds[squares[playerTwoSelection[i] -1 ][j]] = playerColors[1];
    }
    
  }
  FastLED.show();
}

void findNextAvailable(){
  repeatCheck = true;

  while (repeatCheck){
    for (int i = 0; i < 5; i++){
      if (currentLocation == playerOneSelection[i] || currentLocation == playerTwoSelection[i]){
        currentLocation += 1;
        break;
      }
      else if (i == 4){
        repeatCheck = false;
      }
    }
  }
}

void checkWin(int player){
  bool hasOne = false;
  bool hasTwo = false;
  bool hasThree = false;
  bool hasFour = false;
  bool hasFive = false;
  bool hasSix = false;
  bool hasSeven = false;
  bool hasEight = false;
  bool hasNine = false;

  if (player == 1){
    for (int i = 0; i < 5; i++){
      switch (playerOneSelection[i]){
        case 1:
          hasOne = true;
          break;
         case 2:
          hasTwo = true;
          break;
         case 3:
          hasThree = true;
          break;
         case 4:
          hasFour = true;
          break;
         case 5:
          hasFive = true;
          break;
         case 6:
          hasSix = true;
          break;
         case 7:
          hasSeven = true;
          break;
         case 8:
          hasEight = true;
          break;
         case 9:
          hasNine = true;
          break;
      }
    }
  }
  else if (player == 2){
    for (int i = 0; i < 5; i++){
      switch (playerTwoSelection[i]){
        case 1:
          hasOne = true;
          break;
         case 2:
          hasTwo = true;
          break;
         case 3:
          hasThree = true;
          break;
         case 4:
          hasFour = true;
          break;
         case 5:
          hasFive = true;
          break;
         case 6:
          hasSix = true;
          break;
         case 7:
          hasSeven = true;
          break;
         case 8:
          hasEight = true;
          break;
         case 9:
          hasNine = true;
          break;
      }
    }  
  }
  
  if ((hasOne && hasTwo && hasThree) || (hasFour && hasFive && hasSix) || (hasSeven && hasEight && hasNine) || (hasOne && hasFour && hasSeven) || (hasTwo && hasFive && hasEight) || (hasThree && hasSix && hasNine) || (hasOne && hasFive && hasNine) || (hasThree && hasFive && hasSeven)){
    winner(player);
  }
  else if(playerOneArraySize + playerTwoArraySize >= 9){
    noWinner();
  }
  
}

void noWinner(){
   for (int i = 0; i < playerOneArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerOneSelection[i]-1][j]] = playerColors[0];
        }
    }
   for (int i = 0; i < playerTwoArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerTwoSelection[i]-1][j]] = playerColors[1];
        }
    }
   FastLED.show();
   delay(500); 
     for (int i = 0; i < playerOneArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerOneSelection[i]-1][j]] = CRGB(0,0,0);
      }
    }
    for (int i = 0; i < playerTwoArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerTwoSelection[i]-1][j]] = CRGB(0,0,0);
        }
    }
   FastLED.show();
   delay(500); 
    for (int i = 0; i < playerOneArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerOneSelection[i]-1][j]] = playerColors[0];
        }
    }
   for (int i = 0; i < playerTwoArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerTwoSelection[i]-1][j]] = playerColors[1];
      }
    }
   FastLED.show();

   delay(1000);
  
  gameStarted = false;
  playerOneArraySize = 0;
  playerTwoArraySize = 0;
  irrecv.resume();
  delay(100);
  resetLeds();
}

void winner(int player){
  if (player == 1){
    for (int i = 0; i < playerOneArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerOneSelection[i]-1][j]] = playerColors[player-1];
        }
    }
   FastLED.show();
   delay(500); 
     for (int i = 0; i < playerOneArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerOneSelection[i]-1][j]] = CRGB(0,0,0);
      }
    }
   FastLED.show();
   delay(500); 
   for (int i = 0; i < playerOneArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerOneSelection[i]-1][j]] = playerColors[player-1];
      }
    }
   FastLED.show();
  }
  else if (player == 2){
    for (int i = 0; i < playerTwoArraySize; i++){
        for (int j = 0; j < SQ_NUM; j++){
          leds[squares[playerTwoSelection[i]-1][j]] = playerColors[player-1];
        }
    }
   FastLED.show();
   delay(500); 
     for (int i = 0; i < playerTwoArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerTwoSelection[i]-1][j]] = CRGB(0,0,0);
      }
    }
   FastLED.show();
   delay(500); 
   for (int i = 0; i < playerTwoArraySize; i++){
      for (int j = 0; j < SQ_NUM; j++){
        leds[squares[playerTwoSelection[i]-1][j]] = playerColors[player-1];
      }
    }
   FastLED.show();
  }
  delay(1000);
  
  gameStarted = false;
  irrecv.resume();
  playerOneArraySize = 0;
  playerTwoArraySize = 0;
  delay(100);
  resetLeds();
}

void resetLeds(){
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = CRGB(0,0,0);
    }
    FastLED.show();
}
