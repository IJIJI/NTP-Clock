// We need this header file to use FLASH as storage with PROGMEM directive:
#include <avr/pgmspace.h>

// Icon width and height
const uint16_t updateIconGreyWidth = 18;
const uint16_t updateIconGreyHeight = 18;

//Icon Color
#define updateIconGreyColor 0x632C

// The icon file can be created with the "UTFT ImageConverter 565" bitmap to .c file creation utility, more can be pasted in here
const unsigned short  updateIconGrey[324] PROGMEM={
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  0x0000, 0x0000, 0x0000, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 
  updateIconGreyColor, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 
  updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 
  0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 
  updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  updateIconGreyColor, updateIconGreyColor, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 
  updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, updateIconGreyColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000
};


