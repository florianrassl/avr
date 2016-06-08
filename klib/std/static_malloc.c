#include <stdint.h>


#ifndef NULL
#define NULL 0
#endif

static uint8_t *malloc_pool;
static uint16_t size_pool;
static uint8_t *malloc_ptr;

void init_static_malloc(uint8_t *malloc_v_p, uint16_t size_p){
  malloc_pool=malloc_v_p;
  size_pool=size_p;
  malloc_ptr = malloc_pool;
}

void *static_malloc(uint16_t size_p){
  uint8_t *malloc_ptr_t=malloc_ptr;
  if(malloc_ptr + size_p >= malloc_pool+size_pool)
    return NULL;
  malloc_ptr+=size_p;
  return (void*)malloc_ptr_t;
}

