/*
     6
    ---
11|     |7
  |  12 |
    ---
10|     |8
  |     |
    ---
     9

  pin 13 is decimal point

  Digit 1 = Arduino pin 2
  Digit 2 = Arduino pin 3
  Digit 3 = Arduino pin 4
  Digit 4 = Arduino pin 5

Seven segment display pins:                 
-----------------------------------
|      .   .   .   .   .   .      |
|      1   2   3   4   5   6      |  
|      .   .   .   .   .   .      | 
|      7   8   9  10  11  12      | 
----------------------------------- 

Mapping
_______________________________________________________
Arduino pins: [2, 3, 4, 5, 6, 7, 8,  9, 10, 11, 12, 13]
Display pins: [6, 3, 2, 7, 5, 1, 9, 11, 12,  4,  8, 10]
*/

// Arrays of HIGHs and LOWs to define seven-segment numbers
int zero[8]  = {1, 1, 1, 1, 1, 1, 0};
int one[8]   = {0, 1, 1, 0, 0, 0, 0};
int two[8]   = {1, 1, 0, 1, 1, 0, 1};
int three[8] = {1, 1, 1, 1, 0, 0, 1};
int four[8]  = {0, 1, 1, 0, 0, 1, 1};
int five[8]  = {1, 0, 1, 1, 0, 1, 1};
int six[8]   = {1, 0, 1, 1, 1, 1, 1};
int seven[8] = {1, 1, 1, 0, 0, 0, 0};
int eight[8] = {1, 1, 1, 1, 1, 1, 1};
int nine[8]  = {1, 1, 1, 1, 0, 1, 1};

// Pins controlling the four digits
int digit_pins[4] = {2, 3, 4, 5};

// Pins controlling the eight segments (8th is decimal point)
int segment_pins[8] = {6, 7, 8, 9, 10, 11, 12, 13};

// The four digit values to display
int d1 = 0; int d2 = 0; int d3 = 0; int d4 = 0;

// temp
int temp = 0;
unsigned long start_time = millis();