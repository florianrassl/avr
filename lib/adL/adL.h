//autor Florian Rassl
#ifndef _ADL
#define _ADL 1

#include <stdint.h>

extern void adLInit();
extern void rxChar(uint8_t c);
extern char *adLSetChar(char c);
typedef void txOut();
extern void txChar(txOut *out, uint8_t add, int8_t data);
extern void txInt16(txOut *out, uint8_t add, int16_t data);

#endif /*_ADL*/
