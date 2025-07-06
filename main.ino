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

int set_number(int num, int decimal) {
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

    digitalWrite(segment_pins[7], decimal);
}

void set_display(float value) {
    digit1 = floor(value);
    if (value > 10) {
        // for values greater than or equal to 10, the digit1 value
        // is actually the first two digits
        int digit1_new = floor(digit1 / 10);
        int digit2_new = digit1 % 10;
        int digit3_new = floor((value - digit1) * 10);
        int digit4_new = floor((((value - digit1) * 10) - digit3_new) * 10);
        digit1 = digit1_new; digit2 = digit2_new; digit3 = digit3_new; digit4 = digit4_new;
    }
    else {
        digit2 = floor((value - digit1) * 10);
        digit3 = floor((((value - digit1) * 10) - digit2) * 10);
    }
    
    // set first digit
    set_digit_pos(0, 1, 1, 1);
    if (value > 10) {
        set_number(digit1, false);
    }
    else {
        set_number(digit1, true);
    }
    set_all_low();

    // set second digit
    set_digit_pos(1, 0, 1, 1);
    if (value > 10) {
        set_number(digit2, true);
    }
    else {
        set_number(digit2, false);
    }
    set_all_low();
    
    // set third digit
    set_digit_pos(1, 1, 0, 1);
    set_number(digit3, false);
    set_all_low();

    // set fourth digit if needed
    set_digit_pos(1, 1, 1, 0);
    if (value > 10) {
        set_number(digit4, false);
        set_all_low();
    }
}

void set_all_low() {
    for (int i = 0; i < 8; i++) {
        digitalWrite(segment_pins[i], 0);
    }
}
