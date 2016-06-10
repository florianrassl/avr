//autor Florian Rassl
#ifndef _NSH
#define _NSH 1

#include <stdint.h>
#include <string.h>
#include "../include/charDev.h"

extern charDev *nshDev; 

#define nprint(str) charDevPutStr(nshDev,(char*) str)

typedef int8_t toolMethode(char *args[], uint8_t argc);
typedef void toolRxChar(char c);

extern void nshUpdate();
extern void nshInit();
void addTool(toolMethode *toolMethode, char* toolName, toolRxChar toolMethodeRxChar);
typedef char *rxOut(char c); 
extern toolRxChar *toolRxCharM;
extern rxOut *out;

inline int getArgNum(char* argv[], int argc, char arg[], int args){ //sucht nach arg in arg List
  int i;
  for(i=0; i<argc; i++){
    if((i+args)>=argc+1)
      return -1; 
    if(strncmp(argv[i], arg, strlen(arg))==0){
      return i;
    }   
  }   
  return -1; 
}


#endif /*_NSH*/
