

#if defined(AVR) 
#include "avr/pgmspace.h"
#elif __has_include("sys/pgmspace.h.h") 
#include "sys/pgmspace.h"
#else
#include "pgmspace.h"
#endif

//#define PROGMEM
//#define pgm_read_byte(byte) *byte
