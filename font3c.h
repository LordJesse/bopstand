#include <avr/pgmspace.h>

// FONT WIDTH = 16
// FONT_3X_RANGE_START 46 // '.' but instead a space

static const uint8_t font_3c[] PROGMEM = { // digit 0-9 plus an arrow instead of '/' and space instead of '.'

0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // . (set to space)
0x00, 0x00, 0xFF, 0x7F, 0x30, 0x19, 0x0C, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // / (set to arrow)
0x00, 0x0F, 0x1F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00, 0x00, // 1
0x00, 0x70, 0x70, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x71, 0x71, 0x71, 0x70, 0x70, 0x70, 0x70, 0x00, // 2
0x00, 0x0E, 0x1E, 0x7E, 0x7E, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 3
0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x00, // 4
0x00, 0x0E, 0x1E, 0x7E, 0x7E, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 5
0x00, 0x0F, 0x1F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 6
0x00, 0x00, 0x00, 0x78, 0x7E, 0x7F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 7
0x00, 0x0F, 0x1F, 0x7F, 0x7F, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 8
0x00, 0x0E, 0x1E, 0x7E, 0x7E, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x7F, 0x7F, 0x1F, 0x0F, 0x00, // 9
 
};
