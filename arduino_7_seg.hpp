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

//////////////////////////////////////////////////////////////////////////
void init_all_pins() {
  // Must be called at the start of program
  for (int i = 0; i < 9; i++) {
    if (i < 4) {
      pinMode(digit_pins[i], OUTPUT);
    };
    pinMode(segment_pins[i], OUTPUT);
  }
}

void set_digit_pos(int d1, int d2, int d3, int d4){
  // Set position to write number to. d1...4 to be passed in as 0 or 1
  digitalWrite(digit_pins[0], d1);
  digitalWrite(digit_pins[1], d2);
  digitalWrite(digit_pins[2], d3);
  digitalWrite(digit_pins[3], d4);
}

void set_number_from_pin_vals(int pin_vals[7]) {
  for (int i = 0; i < 7; i++) {
      digitalWrite(segment_pins[i], pin_vals[i]);
  }
}

void set_number(int num) {
  int pin_vals[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  if (num == 0) {
      set_number_from_pin_vals(zero);
  }
  else if (num == 1) {
      set_number_from_pin_vals(one);
  }
  else if (num == 2) {
      set_number_from_pin_vals(two);
  }
  else if (num == 3) {
      set_number_from_pin_vals(three);
  }
  else if (num == 4) {
      set_number_from_pin_vals(four);
  }
  else if (num == 5) {
      set_number_from_pin_vals(five);
  }
  else if (num == 6) {
      set_number_from_pin_vals(six);
  }
  else if (num == 7) {
      set_number_from_pin_vals(seven);
  }
  else if (num == 8) {
      set_number_from_pin_vals(eight);
  }
  else if (num == 9) {
      set_number_from_pin_vals(nine);
  }
}

void set_all_low() {
  for (int i = 0; i < 8; i++) {
      digitalWrite(segment_pins[i], 0);
  }
}

void set_display(float value) {
  // Main function
  if (value > 9999) {
    return;
  }
  // Cast value to int for now
  int val = static_cast<int>(value);

  d1 = -1; d2 = -1; d3 = -1;
  d4 = floor(val % 10);
  if (val >= 10) {
    // Two digit number
    d3 = floor((val % 100) / 10);
  }

  if (val >= 100) {
    // Three digit number
    d2 = floor((val % 1000) / 100);
  }
  
  if (val >= 1000) {
    // Four digit number
    d1 = floor(val / 1000);
  }

  // SET DIGITS
  if (d4 != -1) {
    set_digit_pos(1, 1, 1, 0); set_number(d4); set_all_low();
  }
  if (d3 != -1) {
    set_digit_pos(1, 1, 0, 1); set_number(d3); set_all_low();
  }
  if (d2 != -1) {
    set_digit_pos(1, 0, 1, 1); set_number(d2); set_all_low();
  }
  if (d1 != -1) {
    set_digit_pos(0, 1, 1, 1); set_number(d1); set_all_low();
  }
}