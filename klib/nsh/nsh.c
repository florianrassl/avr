//autor Florian Rassl

#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "nsh.h"
#include "../include/charDev.h"
#include "../include/static_list.h"
#include "../include/static_malloc.h"
#include <stdlib.h>

#define BUFFSICE 60
#define ARGS 8

charDev *nshDev;

void convertStrToArry(const char *strIn, const char* args[], uint8_t *argc);
void nshSetChar(char rxC);
static int8_t clearTool(char *args[], uint8_t argc);

void toolGenericInit();
void inline toolPrintPrompt(){ nprint("AVR# "); }
void toolList(const char *args[], uint8_t argc);
void addTool(toolMethode *toolMethode, char* toolName, toolRxChar toolMethodeRxChar);
void autoErgTool(const char *buff, uint8_t buffSice, char **buffPtr);

static const char consoleBuff[BUFFSICE];
static const char* args[ARGS];
static uint8_t rxComplit=0;
static uint8_t argc;

typedef struct tool{
        char *toolName;
        toolMethode *toolMethode;
        toolRxChar *toolMethodeRxChar;
}tool;

static uint8_t toolCount;
static list_element tool_list[1];


char toolFlack;
enum toolFlacks{
        ALIVE, KILL, PAUS
};

//n.t.
toolRxChar *toolRxCharM;

void nshInit(charDev *dev){
  nshDev = dev;
  nshDev->rxChar=&nshSetChar;
  toolGenericInit();
}

void nshUpdate(){
  if(rxComplit){
    toolFlack = ALIVE;
    convertStrToArry(consoleBuff, (const char **)args, &argc);
    toolRxCharM = NULL;
    toolList((const char**)args, argc);
    rxComplit = 0;
  }
}

void convertStrToArry(const char *strIn, const char* args[], uint8_t *argc){
  char *strInPtr = (char*)strIn;
  char **strArgsPtr = (char**)args;
  (*argc)=0;
  if(strlen(strInPtr) == 0)
    return;
  if(*strInPtr!= ' ' && *strInPtr != '\r' && *strInPtr != '\n'){
    *strArgsPtr = strInPtr;
    strArgsPtr++;
    (*argc)++;
  }
  for(; *strInPtr != '\0'; strInPtr++){
    if(*strInPtr == ' '){
      *strInPtr = '\0';
      if(*(strInPtr+1) == ' ' || *(strInPtr+1) == '\r' || *(strInPtr+1) == '\n' || 
        *(strInPtr+1) == '\0')
        continue;
      (*argc)++;
      if((*argc) >= ARGS){
	(*argc) = 0;
        return;
      }
      *strArgsPtr = strInPtr+1;
      strArgsPtr++;
    }
  }
}

#define STRG '#' //STRG TASTE

void nshSetChar(char rxC){
  static char txS[6];
  static char *inBuffPtr = (char*)consoleBuff;
  static char oldRxC=0;

  if(oldRxC == STRG && rxC == 'c'){
    toolFlack = KILL;
    inBuffPtr = (char*)consoleBuff; 
    strcpy(txS, "^c\n\r");
    oldRxC = 0;
  }
  //wird beim laufenden tool ausgefürt   
  else if(rxComplit == 1){	
    if(toolRxCharM!=NULL)
      toolRxCharM(rxC);
    *txS='\0';
  }
  //zeilen umbruch d.h. tool wierd gestarted
  else if(rxC == '\r' || rxC == '\n' /*|| rxComplit == 1*/){ //n.c.
    *inBuffPtr = '\0';
    inBuffPtr = (char*)consoleBuff;
    rxComplit = 1;
    strcpy(txS, "\n\r");
  }
  //zeichen wird gelöscht
  else if(rxC == '\b' || rxC == 127){
    if(inBuffPtr > consoleBuff){
      inBuffPtr--;
      nprint("\b \b");
      return;
    }
    strcpy(txS, "");
  }
  //buffer oferflow
  else if(inBuffPtr >= consoleBuff+BUFFSICE-2){
    strcpy(txS, "bof\n\r");
  }

  else if(rxC == '\t'){
    (*inBuffPtr)= '\0';
    autoErgTool(consoleBuff, BUFFSICE, &inBuffPtr);
    oldRxC='\0';
    *txS='\0';
  }
  //steuerzeichen entfärnen
  else if(rxC < 0x20){
    *txS='\0';
  }
  //zeichen wierd in buffer kopiert
  else{
    (*inBuffPtr)= rxC;
    inBuffPtr++;
    //
    txS[0] = rxC;
    txS[1] = '\0';
  }
  oldRxC = rxC;
  nprint(txS);
  return ;
}

#include "tools.h"

void toolGenericInit(){ // selbsterklären
  toolCount=0;
  addTool(&clearTool, "clear", NULL);
  #ifdef _PORTTOOL
  addTool(&portTool, "port", NULL);
  #endif
  #ifdef _SERVOTOOL
  addTool(&servoTool, "servo", NULL);
  #endif
  #ifdef _ADCTOOL
  addTool(&adcTool, "adc", NULL);
  #endif
  toolPrintPrompt();
}

void addTool(toolMethode *toolMethode, char* toolName, toolRxChar toolMethodeRxChar){ //fürt ein tool hinzu
  tool *tmp = static_malloc(sizeof(tool));
  if(list_add_data(tool_list, (void*)tmp) != 0 || tmp == NULL){
    nprint("s_m_e\n\r");
    return;
  }
  tmp->toolName = toolName;
  tmp->toolMethode = toolMethode;
  tmp->toolMethodeRxChar =toolMethodeRxChar;
  toolCount++;
}

void toolList(const char *args[], uint8_t argc){ //sucht tool in liste.
  char** argsPtr = (char**)args;
  list_element *el;
  if(argc>0){
    for(el=tool_list->next; el!=NULL; el=el->next){
      if(!strcmp(args[0], ((tool*)el->data)->toolName)){
        toolRxCharM = ((tool*)el->data)->toolMethodeRxChar;
        while(((tool*)el->data)->toolMethode(&argsPtr[1], argc-1) && toolFlack!=KILL);
        break;
      }
    }
    if(el==NULL){
      nprint(args[0]);
      nprint(": command not found\n\r");
    }
  }
  toolPrintPrompt();
}

void autoErgTool(const char *buff, uint8_t buffSice, char **buffPtr){ //sucht nach argg0 und ergänzst dises 
  list_element *el, *tel;
  uint8_t n=0;
  for(el=tool_list->next; el!=NULL; el=el->next){
    if(!strncmp(buff, ((tool*)el->data)->toolName, strlen(buff))){
      n++;
      tel=el;
    }
  }
  for(el=tool_list->next; el!=NULL; el=el->next){
    if(!strncmp(buff, ((tool*)el->data)->toolName, strlen(buff))){
      if(n>1){
        nprint("\r\n");
        nprint(((tool*)el->data)->toolName);
        nprint("\t");
      }
    }
  }
  if(n){
    if(n==1){
      strncpy((char*)buff, ((tool*)tel->data)->toolName, buffSice-2);
      nprint(*buffPtr);
      *buffPtr=(char*)buff+strlen(buff);
    }
    else{
      nprint("\n\r");
      toolPrintPrompt();
      nprint(buff);
    }
  }
}

static int8_t clearTool(char *args[], uint8_t argc){ // selbsterklärend
  (void)args;
  (void)argc;
  nprint("\x1B[2J\x1B[H");
  return 0;
}
