#include "consts.hpp"

void set_display(float value) {
    if (value > 9999) {
      return;
    }

    d1 = -1; d2 = -1; d3 = -1
    d4 = value % 10;

    if (value >= 10) {
      // Two digit number
      d3 = floor((value % 100) / 10)
    }

    if (value >= 100) {
      // Three digit number
      d2 = floor((value % 1000) / 100)
    }
    
    if (value >= 1000) {
      // Four digit number
      d1 = floor(value / 1000);
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