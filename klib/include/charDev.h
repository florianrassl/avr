#ifndef _CHARDEV 
#define _CHARDEV 1

#include <stdint.h>
#ifndef NULL
#define NULL 0
#endif

typedef void _putChar(char c);
typedef char _getChar();
typedef void _rxChar(char c);

typedef struct charDev{
  _putChar *putChar;
  _getChar *getChar;
  _rxChar *rxChar;
  //char open;
}charDev;

inline void charDevPutStr( charDev *dev, char *str){
 //test if putChar == NULL --> return -1 
 char *stri = (char*)str;
  for(; (*stri)!= '\0'; stri++){
    dev->putChar(*stri);
  }
}

inline void charDevPutBlock( charDev *dev, void *block, uint16_t sice){
  char *blocki = (char*)block;
  for(; blocki<(char*)(block+sice); blocki++)
    dev->putChar(*blocki);
  
}

#endif /*_CHARDEV*/
