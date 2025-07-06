// arrays of HIGHs and LOWs to define seven-segment numbers
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

// pins controlling the four digits
int digit_pins[4] = {2, 3, 4, 5};

// pins controlling the eight segments (8th is decimal point)
int segment_pins[8] = {6, 7, 8, 9, 10, 11, 12, 13};
