
#ifndef _CONSOLE
#define _CONSOLE 1

#include "tool.h"

extern void consoleUpdate();
extern char *consoleSetChar(char c);
extern void consoleInit();
typedef char *rxOut(char c);
extern toolRxChar *toolRxCharM;
extern rxOut *out;

#endif /*_CONSOE*/
