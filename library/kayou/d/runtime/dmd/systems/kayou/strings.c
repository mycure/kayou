#include "system.h"

// strlen()

size_t strlen(char* s)
{
  register const char *p;

  for (p=s ; *p ; p++);

  return p - s;
}

