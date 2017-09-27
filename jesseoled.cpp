// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <avr/io.h>

#include <avr/pgmspace.h>
#include <TinyWireM.h>
#include "font.h"
#include "font3a.h"
#include "font3b.h"
#include "font3c.h"
#include "jesseoled.h"

// ----------------------------------------------------------------------------

/*

  SSD1306_minimal.h - SSD1306 OLED Driver Library
  2015 Copyright (c) CoPiino Electronics All right reserved.

  Original Author: GOF Electronics Co. Ltd.
  Modified by: CoPiino Electronics ( http://copiino.cc )

  CoPiino Electronics invests time and resources providing this open source code,
  please support CoPiino Electronics and open-source hardware by purchasing
  products from CoPiino Electronics!

  What is it?
    This library is derived from GOFi2cOLED library, only for SSD1306 in I2C Mode.
    As the original library only supports Frame Buffered mode which requires to have
    at least 1024bytes of free RAM for a 128x64px display it is too big for smaller devices.

    So this a SSD1306 library that works great with ATTiny85 devices :)


  It is a free software; you can redistribute it and/or modify it
  under the terms of BSD license, check license.txt for more information.
  All text above must be included in any redistribution.
*/



void SSD1306_Mini::sendCommand(unsigned char command)
{
  Wire.beginTransmission(SlaveAddress); // begin I2C communication
  Wire.send(GOFi2cOLED_Command_Mode);      // Set OLED Command mode
  Wire.send(command);
  Wire.endTransmission();            // End I2C communication
}

void SSD1306_Mini::sendData(unsigned char Data)
{
  Wire.beginTransmission(SlaveAddress); // begin I2C transmission
  Wire.send(GOFi2cOLED_Data_Mode);            // data mode
  Wire.send(Data);
  Wire.endTransmission();                    // stop I2C transmission
}

const uint8_t init_sequence [] PROGMEM = {  // Initialization Sequence
  0xAE,     // Display OFF (sleep mode)
  0x20, 0b00,   // Set Memory Addressing Mode
  // 00=Horizontal Addressing Mode; 01=Vertical Addressing Mode;
  // 10=Page Addressing Mode (RESET); 11=Invalid
  0xB0,     // Set Page Start Address for Page Addressing Mode, 0-7
  0xC8,     // Set COM Output Scan Direction
  0x00,     // ---set low column address
  0x10,     // ---set high column address
  0x40,     // --set start line address
  0x81, 0x3F,   // Set contrast control register
  0xA1,     // Set Segment Re-map. A0=address mapped; A1=address 127 mapped.
  0xA6,     // Set display mode. A6=Normal; A7=Inverse
  0xA8, 0x3F,   // Set multiplex ratio(1 to 64)
  0xA4,     // Output RAM to Display
  // 0xA4=Output follows RAM content; 0xA5,Output ignores RAM content
  0xD3, 0x00,   // Set display offset. 00 = no offset
  0xD5,     // --set display clock divide ratio/oscillator frequency
  0xF0,     // --set divide ratio
  0xD9, 0x22,   // Set pre-charge period
  0xDA, 0x12,   // Set com pins hardware configuration
  0xDB,     // --set vcomh
  0x20,     // 0x20,0.77xVcc
  0x8D, 0x14,   // Set DC-DC enable
  0xAF      // Display ON in normal mode

};

void SSD1306_Mini::init(uint8_t address)
{
  Wire.begin();

  for (uint8_t i = 0; i < sizeof (init_sequence); i++) {
    sendCommand(pgm_read_byte(&init_sequence[i]));
  }
  clear();
}

void SSD1306_Mini::clipArea(unsigned char col, unsigned char row, unsigned char w, unsigned char h) {

  TinyWireM.begin();                    //initialize I2C
  TinyWireM.beginTransmission(SlaveAddress); // begin I2C transmission
  TinyWireM.send(GOFi2cOLED_Command_Mode);            // data mode
  TinyWireM.send(Set_Column_Address_Cmd);
  TinyWireM.send(0);

  TinyWireM.send(col);
  TinyWireM.send(col + w - 1);

  TinyWireM.endTransmission();                    // stop I2C transmission

  TinyWireM.begin();                    //initialize I2C
  TinyWireM.beginTransmission(SlaveAddress); // begin I2C transmission
  TinyWireM.send(GOFi2cOLED_Command_Mode);            // data mode
  TinyWireM.send(Set_Page_Address_Cmd);
  TinyWireM.send(0);

  TinyWireM.send(row);
  TinyWireM.send(row + h - 1);

  TinyWireM.endTransmission();                    // stop I2C transmission

}

void SSD1306_Mini::cursorTo(unsigned char col, unsigned char row) {
  clipArea(col, row, 128 - col, 8 - row);
  /*
    TinyWireM.begin();                    //initialize I2C
    TinyWireM.beginTransmission(SlaveAddress); // begin I2C transmission
    TinyWireM.send(GOFi2cOLED_Command_Mode);            // data mode
    TinyWireM.send(Set_Column_Address_Cmd);
    TinyWireM.send(0);

    TinyWireM.send(col);
    TinyWireM.send(127);

    TinyWireM.endTransmission();                    // stop I2C transmission

    TinyWireM.begin();                    //initialize I2C
    TinyWireM.beginTransmission(SlaveAddress); // begin I2C transmission
    TinyWireM.send(GOFi2cOLED_Command_Mode);            // data mode
    TinyWireM.send(Set_Page_Address_Cmd);
    TinyWireM.send(0);

    TinyWireM.send(row);
    TinyWireM.send(7);

    TinyWireM.endTransmission();                    // stop I2C transmission
  */
}

/*
  void SSD1306_Mini::cursorToX( unsigned char row, unsigned char col ){

  sendCommand(0x00 | (0x0F & col) );  // low col = 0
  sendCommand(0x10 | (0x0F & (col>>4)) );  // hi col = 0
  //  sendCommand(0x40 | (0x0F & row) ); // line #0

  sendCommand(0xb0 | (0x03 & row) );  // hi col = 0


  }
*/

void SSD1306_Mini::startScreen() {

  sendCommand(0x00 | 0x0);  // low col = 0
  sendCommand(0x10 | 0x0);  // hi col = 0
  sendCommand(0x40 | 0x0); // line #0

}

void SSD1306_Mini::clear() {

  sendCommand(0x00 | 0x0);  // low col = 0
  sendCommand(0x10 | 0x0);  // hi col = 0
  sendCommand(0x40 | 0x0); // line #0

  clipArea(0, 0, 128, 8);

  for (uint16_t i = 0; i <= ((128 * 64 / 8) / 16); i++)
  {
    // send a bunch of data in one xmission
    Wire.beginTransmission(SlaveAddress);
    Wire.send(GOFi2cOLED_Data_Mode);            // data mode
    for (uint8_t k = 0; k < 16; k++) {
      Wire.send( 0 );
    }
    Wire.endTransmission();
  }
}

void SSD1306_Mini::send_byte(uint8_t byte)
{ if (Wire.writeAvailable()) {
    Wire.endTransmission();
    Wire.beginTransmission(SlaveAddress);
    Wire.send(GOFi2cOLED_Data_Mode);
  }
  Wire.send(byte);

}

void SSD1306_Mini::printCharS(int xpos, int ypos, char ch ) {
  cursorTo(xpos, ypos);
  uint8_t i = 0;
  uint8_t ci = ch - 32;
  Wire.beginTransmission(SlaveAddress);
  Wire.send(GOFi2cOLED_Data_Mode);            // data mode
  for (i = 0; i < 6; i++)
  {
    Wire.send( pgm_read_byte(&font_sm[ci * 6 + i]) );
  }
  Wire.endTransmission();
}

void SSD1306_Mini::printCharL(int xpos, int ypos, char ch ) {
  cursorTo(xpos, ypos);
  uint8_t i = 0;
  if (ch == 32) ch = 46;
  uint8_t ci = ch - 46;
  Wire.beginTransmission(SlaveAddress);
  Wire.send(GOFi2cOLED_Data_Mode);            // data mode
  for (i = 0; i < 24; i++)
  {
    Wire.send( pgm_read_byte(&font_3a[ci * 24 + i]) );
  }
  Wire.endTransmission();
  cursorTo(xpos, ypos + 1);
  Wire.beginTransmission(SlaveAddress);
  Wire.send(GOFi2cOLED_Data_Mode);            // data mode
  for (i = 0; i < 24; i++)
  {
    Wire.send( pgm_read_byte(&font_3b[ci * 24 + i]) );
  }
  Wire.endTransmission();
  cursorTo(xpos, ypos + 2);
  Wire.beginTransmission(SlaveAddress);
  Wire.send(GOFi2cOLED_Data_Mode);            // data mode
  for (i = 0; i < 24; i++)
  {
    Wire.send( pgm_read_byte(&font_3c[ci * 24 + i]) );
  }
  Wire.endTransmission();
}



void SSD1306_Mini::printStringS(int xst, int yst,  char * pText ) {
  uint8_t i = 0;
  unsigned char len = strlen( pText );

  for (i = 0; i < len; i++) {
    printCharS(xst + (i * 6), yst, pText[i] );
  }
}

void SSD1306_Mini::printStringL(int xst, int yst,  char * pText ) {
  uint8_t i = 0;
  unsigned char len = strlen( pText );

  for (i = 0; i < len; i++) {
    printCharL(xst + (i * 24), yst, pText[i] );
  }
}



void SSD1306_Mini::drawImage(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const uint8_t bitmap[])
{
  uint16_t j = 0;
  uint8_t y, x;

  for (y = y0; y < y1; y++)
  {
    cursorTo(x0, y0);
    Wire.beginTransmission(SlaveAddress);
    Wire.send(GOFi2cOLED_Data_Mode);
    for (x = x0; x < x1; x++)
    {
      Wire.send(pgm_read_byte(&bitmap[j++]));
    }
    Wire.endTransmission();
  }
  cursorTo(0, 0);
}


