#ifndef STATIC_LIST
#define STATIC_LIST 1

#include "static_malloc.h"

typedef struct list_element{
  struct list_element *next;
  void *data;
}list_element;

inline list_element *list_get_next_element(list_element *le){
  return le->next;
}

inline list_element *list_get_last_element(list_element *le){
  for(;le->next != NULL; le=le->next);
  return le;
}

inline void list_add_element(list_element *list, list_element *new_element){
  list=list_get_last_element(list);
  new_element->next=NULL;
  list->next = new_element;
}

inline int8_t list_add_data(list_element *list, void* data){
  list = list_get_last_element(list);
  list->next = static_malloc(sizeof(list_element));
  if(list->next == NULL) return -1;
  list->next->data = data;
  return 0;
}
#endif
