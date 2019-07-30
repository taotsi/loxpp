#ifndef CLOX_MEMORY_HH
#define CLOX_MEMORY_HH

#include "clox_common.hh"

#define GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (capacity)*2)

#define GROW_ARRAY(previous, type, old_size, new_size) \
  (type*)Reallocate(previous, sizeof(type)*(old_size), sizeof(type)*(new_size))

#define FREE_ARRAY(type, pointer, old_size) \
  Reallocate(pointer, sizeof(type)*(old_size), 0)

void* Reallocate(void* previous, size_t old_size, size_t new_size);

#endif // CLOX_MEMORY_HH