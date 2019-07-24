#include <stdlib.h>
#include "clox_memory.h"

void* Reallocate(void* previous, size_t old_size, size_t new_size){
  if(new_size == 0){
    free(previous);
    return NULL;
  }
  return realloc(previous, new_size);
}