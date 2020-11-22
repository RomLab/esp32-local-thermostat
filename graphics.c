#ifndef FONT5X7_H
#define FONT5X7_H

#ifdef __AVR__
#include <avr/io.h>
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#elif defined(__IMXRT1052__) || defined(__IMXRT1062__)
// PROGMEM is defefind for T4 to place data in specific memory section
#undef PROGMEM
#define PROGMEM
#else
#define PROGMEM
#endif

const unsigned char online []PROGMEM ={
0x00,0x00,0x00,
0x00,0x00,0x00,
0x01,0xFC,0x00,
0x0F,0xFF,0x00,
0x3F,0xFF,0xC0,
0x7F,0xFF,0xE0,
0xFC,0x03,0xF0,
0x70,0x00,0xE0,
0x21,0xF8,0x40,
0x07,0xFE,0x00,
0x0F,0xFF,0x00,
0x07,0x9E,0x00,
0x02,0x04,0x00,
0x00,0x00,0x00,
0x00,0xF0,0x00,
0x00,0xF0,0x00,
0x00,0xF0,0x00,
0x00,0x60,0x00,
0x00,0x00,0x00,
0x00,0x00,0x00 
};

const unsigned char offline []PROGMEM ={
0x00,0x00,0x00,
0x00,0x00,0x00,
0x30,0x00,0x00,
0x3B,0xFC,0x00,
0x1D,0xFF,0x80,
0x2E,0xFF,0xC0,
0xF7,0x0F,0xF0,
0x7B,0x81,0xE0,
0x31,0xC0,0xC0,
0x02,0xEC,0x00,
0x07,0x76,0x00,
0x0F,0xBB,0x00,
0x07,0x1C,0x00,
0x02,0x0E,0x00,
0x00,0x07,0x00,
0x00,0xF3,0x00,
0x00,0xF0,0x00,
0x00,0xF0,0x00,
0x00,0x60,0x00,
0x00,0x00,0x00 
};

const unsigned char title []PROGMEM ={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0xf,0xc0,0x0,0x3,0xf8,0x0,0x7,0xff,0xf0,0x0,0x0,0x7,0xff,0xe0,0x0,0x7,0xf0,0x3,0xff,0xc0,0xf,0xff,0xf0,0x1,0xfc,0x0,0x0,0x0,0x7f,0x0,0xff,0x0,0x3f,0xc0,
0x0,0x7f,0xfc,0x0,0x3,0xf8,0x0,0xf,0xff,0xfe,0x0,0x0,0x7,0xff,0xfc,0x0,0xf,0xf0,0x7,0xff,0xf0,0xf,0xff,0xfc,0x1,0xfc,0x0,0x0,0x0,0x7f,0x0,0xff,0x0,0x3f,0xc0,
0x1,0xff,0xff,0x0,0x7,0xf8,0x0,0xf,0xff,0xff,0x0,0x0,0x7,0xff,0xff,0x0,0xf,0xf0,0xf,0xff,0xf8,0xf,0xff,0xff,0x1,0xfc,0x0,0x0,0x0,0xff,0x0,0x7f,0x80,0x7f,0x80,
0x3,0xff,0xff,0x0,0x7,0xfc,0x0,0xf,0xff,0xff,0x80,0x0,0x7,0xff,0xff,0x80,0xf,0xf0,0x1f,0xff,0xfc,0xf,0xff,0xff,0x1,0xfc,0x0,0x0,0x0,0xff,0x80,0x7f,0x80,0x7f,0x80,
0x7,0xff,0xff,0x0,0xf,0xfc,0x0,0xf,0xff,0xff,0xc0,0x0,0x7,0xff,0xff,0xc0,0xf,0xf0,0x3f,0xff,0xfc,0xf,0xff,0xff,0x81,0xfc,0x0,0x0,0x1,0xff,0x80,0x3f,0xc0,0xff,0x0,
0xf,0xff,0xfe,0x0,0xf,0xfe,0x0,0xf,0xff,0xff,0xe0,0x0,0x7,0xff,0xff,0xe0,0xf,0xf0,0x3f,0xff,0xf8,0xf,0xff,0xff,0xc1,0xfc,0x0,0x0,0x1,0xff,0xc0,0x1f,0xc0,0xff,0x0,
0x1f,0xff,0xfc,0x0,0xf,0xfe,0x0,0xf,0xf0,0x3f,0xe0,0x0,0x7,0xff,0xff,0xf0,0xf,0xf0,0x3f,0xc1,0xf8,0xf,0xe0,0x3f,0xc1,0xfc,0x0,0x0,0x1,0xff,0xc0,0x1f,0xe1,0xfe,0x0,
0x3f,0xf0,0x38,0x0,0x1f,0xfe,0x0,0xf,0xf0,0x1f,0xf0,0x0,0x7,0xf0,0x1f,0xf8,0xf,0xf0,0x3f,0x80,0x70,0xf,0xe0,0x1f,0xc1,0xfc,0x0,0x0,0x3,0xff,0xc0,0xf,0xe1,0xfe,0x0,
0x3f,0xe0,0x0,0x0,0x1f,0xff,0x0,0xf,0xf0,0xf,0xf0,0x0,0x7,0xf0,0xf,0xf8,0xf,0xf0,0x3f,0x80,0x0,0xf,0xe0,0x1f,0xc1,0xfc,0x0,0x0,0x3,0xff,0xe0,0xf,0xf3,0xfc,0x0,
0x7f,0xc0,0x0,0x0,0x1f,0xbf,0x0,0xf,0xf0,0xf,0xf0,0x0,0x7,0xf0,0x7,0xfc,0xf,0xf0,0x3f,0xc0,0x0,0xf,0xe0,0x1f,0xe1,0xfc,0x0,0x0,0x3,0xf7,0xe0,0x7,0xf3,0xf8,0x0,
0x7f,0x80,0x0,0x0,0x3f,0xbf,0x80,0xf,0xf0,0xf,0xf0,0x0,0x7,0xf0,0x3,0xfc,0xf,0xf0,0x1f,0xf0,0x0,0xf,0xe0,0x1f,0xe1,0xfc,0x0,0x0,0x7,0xf7,0xf0,0x7,0xfb,0xf8,0x0,
0x7f,0x0,0x0,0x0,0x3f,0x3f,0x80,0xf,0xf0,0xf,0xf0,0x0,0x7,0xf0,0x1,0xfc,0xf,0xf0,0x1f,0xfe,0x0,0xf,0xe0,0x1f,0xc1,0xfc,0x0,0x0,0x7,0xe7,0xf0,0x3,0xff,0xf0,0x0,
0xff,0x0,0x0,0x0,0x7f,0x1f,0x80,0xf,0xf0,0x1f,0xe0,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0xf,0xff,0x80,0xf,0xe0,0x3f,0xc1,0xfc,0x0,0x0,0xf,0xe3,0xf0,0x3,0xff,0xf0,0x0,
0xff,0x0,0x0,0x0,0x7f,0x1f,0xc0,0xf,0xf0,0x3f,0xe0,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0x7,0xff,0xe0,0xf,0xff,0xff,0xc1,0xfc,0x0,0x0,0xf,0xe3,0xf8,0x1,0xff,0xe0,0x0,
0xff,0x0,0x0,0x0,0x7e,0x1f,0xc0,0xf,0xff,0xff,0xe0,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0x3,0xff,0xf8,0xf,0xff,0xff,0x81,0xfc,0x0,0x0,0xf,0xc3,0xf8,0x0,0xff,0xe0,0x0,
0xff,0x0,0x0,0x0,0xfe,0xf,0xc0,0xf,0xff,0xff,0xc0,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0x0,0xff,0xfc,0xf,0xff,0xff,0x81,0xfc,0x0,0x0,0x1f,0xc1,0xf8,0x0,0xff,0xc0,0x0,
0xff,0x0,0x0,0x0,0xfe,0xf,0xe0,0xf,0xff,0xff,0x80,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0x0,0x3f,0xfe,0xf,0xff,0xff,0x1,0xfc,0x0,0x0,0x1f,0xc1,0xfc,0x0,0x7f,0x80,0x0,
0xff,0x0,0x0,0x1,0xfc,0xf,0xe0,0xf,0xff,0xff,0x0,0x0,0x7,0xf0,0x1,0xfe,0xf,0xf0,0x0,0x7,0xfe,0xf,0xff,0xfc,0x1,0xfc,0x0,0x0,0x3f,0x81,0xfc,0x0,0x7f,0x80,0x0,
0x7f,0x0,0x0,0x1,0xff,0xff,0xf0,0xf,0xff,0xfe,0x0,0x0,0x7,0xf0,0x1,0xfc,0xf,0xf0,0x0,0x1,0xfe,0xf,0xff,0xf0,0x1,0xfc,0x0,0x0,0x3f,0xff,0xfe,0x0,0x7f,0x80,0x0,
0x7f,0x80,0x0,0x1,0xff,0xff,0xf0,0xf,0xff,0xfe,0x0,0x0,0x7,0xf0,0x3,0xfc,0xf,0xf0,0x0,0x0,0xfe,0xf,0xe0,0x0,0x1,0xfc,0x0,0x0,0x3f,0xff,0xfe,0x0,0x7f,0x80,0x0,
0x7f,0xc0,0x0,0x3,0xff,0xff,0xf0,0xf,0xf0,0xff,0x0,0x0,0x7,0xf0,0x7,0xfc,0xf,0xf0,0xe,0x0,0xfe,0xf,0xe0,0x0,0x1,0xfc,0x0,0x0,0x7f,0xff,0xfe,0x0,0x7f,0x80,0x0,
0x3f,0xe0,0x0,0x3,0xff,0xff,0xf8,0xf,0xf0,0xff,0x80,0x0,0x7,0xf0,0xf,0xf8,0xf,0xf0,0x1f,0x0,0xfe,0xf,0xe0,0x0,0x1,0xfc,0x0,0x0,0x7f,0xff,0xff,0x0,0x7f,0x80,0x0,
0x3f,0xf0,0x38,0x3,0xff,0xff,0xf8,0xf,0xf0,0x7f,0x80,0x0,0x7,0xf0,0x3f,0xf8,0xf,0xf0,0x3f,0x81,0xfe,0xf,0xe0,0x0,0x1,0xfc,0x0,0x0,0x7f,0xff,0xff,0x0,0x7f,0x80,0x0,
0x1f,0xff,0xfc,0x7,0xff,0xff,0xfc,0xf,0xf0,0x7f,0xc0,0x0,0x7,0xff,0xff,0xf0,0xf,0xf0,0x7f,0xff,0xfe,0xf,0xe0,0x0,0x1,0xff,0xff,0xc0,0xff,0xff,0xff,0x80,0x7f,0x80,0x0,
0xf,0xff,0xfe,0x7,0xff,0xff,0xfc,0xf,0xf0,0x3f,0xc0,0x0,0x7,0xff,0xff,0xe0,0xf,0xf0,0x7f,0xff,0xfe,0xf,0xe0,0x0,0x1,0xff,0xff,0xc0,0xff,0xff,0xff,0x80,0x7f,0x80,0x0,
0x7,0xff,0xff,0xf,0xf0,0x1,0xfc,0xf,0xf0,0x3f,0xe0,0x0,0x7,0xff,0xff,0xc0,0xf,0xf0,0x3f,0xff,0xfc,0xf,0xe0,0x0,0x1,0xff,0xff,0xc1,0xfe,0x0,0x3f,0x80,0x7f,0x80,0x0,
0x3,0xff,0xff,0xf,0xe0,0x1,0xfe,0xf,0xf0,0x1f,0xe0,0x0,0x7,0xff,0xff,0x80,0xf,0xf0,0x1f,0xff,0xf8,0xf,0xe0,0x0,0x1,0xff,0xff,0xc1,0xfc,0x0,0x3f,0xc0,0x7f,0x80,0x0,
0x1,0xff,0xff,0xf,0xe0,0x0,0xfe,0xf,0xf0,0x1f,0xf0,0x0,0x7,0xff,0xff,0x0,0xf,0xf0,0xf,0xff,0xf0,0xf,0xe0,0x0,0x1,0xff,0xff,0xc1,0xfc,0x0,0x1f,0xc0,0x7f,0x80,0x0,
0x0,0x7f,0xfc,0x1f,0xe0,0x0,0xfe,0xf,0xf0,0xf,0xf0,0x0,0x7,0xff,0xfc,0x0,0xf,0xf0,0x3,0xff,0xc0,0xf,0xe0,0x0,0x1,0xff,0xff,0xc3,0xfc,0x0,0x1f,0xc0,0x7f,0x80,0x0,
0x0,0xf,0xc0,0x1f,0xc0,0x0,0x7f,0x7,0xf0,0xf,0xf0,0x0,0x7,0xff,0xe0,0x0,0x7,0xf0,0x0,0x7e,0x0,0xf,0xe0,0x0,0x1,0xff,0xff,0xc3,0xf8,0x0,0xf,0xe0,0x7f,0x80,0x0
};

#endif // FONT5X7_H
