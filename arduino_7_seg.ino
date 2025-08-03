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

  pin 13 is decimal point (probably don't need)

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
__________________________________________________
Arduino pins: [2, 3, 4, 5, 6, 7, 8,  9, 10, 11, 12, 13]
Display pins: [6, 3, 2, 7, 5, 1, 9, 11, 12,  4,  8, 10]
*/

#include "consts.hpp"

int init_all_pins() {
  // Must be called at the start of program
  for (int i = 0; i < 9; i++) {
    if (i < 4) {
      pinMode(digit_pins[i], OUTPUT);
    };
    pinMode(segment_pins[i], OUTPUT);
  }
}

int set_digit_pos(int d1, int d2, int d3, int d4){
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

int set_number(int num) {
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

int extract_d1(int val) {
  return floor(val / 1000);
}

int extract_d2(int val, int d4, int d3) {
  // d4 and d3 values needed to calculate
  return ((val - d3*10 - d4) / 100) % 10;
}

int extract_d3(int val, int d4) {
  // d4 value needed to calculate
  return ((val - d4) / 10) % 10;
}

int extract_d4(int val) {
  return val % 10;
}

void set_display(float value) {
    if (value > 9999) {
      return;
    }

    d1 = -1; d2 = -1; d3 = -1; d4 = -1;
    if (value < 10) {
      d4 = extract_d4(value);
    }
    else if ((value >= 10) && (value < 100)) {
      // Only set third and fourth digits
      d4 = extract_d4(value);
      d3 = extract_d3(value, d4);
    }
    else if ((value >= 100) && (value < 1000)) {
      // Only set second, third and fourth digits
      d4 = extract_d4(value);
      d3 = extract_d3(value, d4);
      d2 = extract_d2(value, d4, d3);
    }
    else if (value > 1000) {
      d4 = extract_d4(value);
      d3 = extract_d3(value, d4);
      d2 = extract_d2(value, d4, d3);
      d1 = extract_d1(value);
    }

    // Set fourth digit
    if (d4 != -1) {
      set_digit_pos(1, 1, 1, 0); set_number(d4); set_all_low();
    }

    // Set third digit
    if (d3 != -1) {
      set_digit_pos(1, 1, 0, 1); set_number(d3); set_all_low();
    }

    // Set second digit
    if (d2 != -1) {
      set_digit_pos(1, 0, 1, 1); set_number(d2); set_all_low();
    }

    // Set first digit
    if (d1 != -1) {
      set_digit_pos(0, 1, 1, 1); set_number(d1); set_all_low();
    }
}

void set_all_low() {
    for (int i = 0; i < 8; i++) {
        digitalWrite(segment_pins[i], 0);
    }
}

void setup() {
  init_all_pins();
  // Serial.begin(9600);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - start_time > 500) {
    temp += 1;
    start_time = millis();
  }
  set_display(temp);
}