// We need this header file to use FLASH as storage with PROGMEM directive:
#include <avr/pgmspace.h>

// Icon width and height
const uint16_t updateIconWidth = 18;
const uint16_t updateIconHeight = 18;

//Icon Color
#define updateIconColor 0xffff

// The icon file can be created with the "UTFT ImageConverter 565" bitmap to .c file creation utility, more can be pasted in here
const unsigned short  updateIcon[324] PROGMEM={
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  0x0000, 0x0000, 0x0000, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 
  ethernetIconColor, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 
  ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 
  0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 
  ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  ethernetIconColor, ethernetIconColor, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, 
  ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, ethernetIconColor, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000
};


