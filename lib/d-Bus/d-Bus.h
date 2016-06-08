//autor Florian Rassl

#ifndef _D_BUS
#define _D_BUS 1

#include <stdint.h>

#define DBUSSIZE 20
#define SYSDATASIZE 5

extern int8_t *getDataPtr(uint8_t add);
extern void d_busTool(char *args[], uint8_t argc);

/*********SYSTEM KONSTANTEN:*/
#define PARSADD 		0		//PARS METHODE
#define PARSMETHCONSOLE 0		//Console
#define PARSMETHRXB8	1		//RXB8
#define PARSMETHADL		2		//adL

#define LEDADD			1		//LED



#endif /*_D_BUS*/
