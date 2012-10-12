#include "system.h"

// memcpy()

void* memcpy(void* s1, void* s2, unsigned int n)
{
  register char *r1 = s1;
  register const char *r2 = s2;

  while (n--) {
    *r1++ = *r2++;
  }

  return s1;
}

// memmove()

void* memmove(void* s1, void* s2, size_t n)
{
  register char *s = (char *) s1;
  register const char *p = (const char *) s2;

  if (p >= s) {
    while (n--) {
      *s++ = *p++;
    }
  } else {
    s += n;
    p += n;
    while (n--) {
      *--s = *--p;
    }
  }

  return s1;
}

// memcmp()

int memcmp(void* s1, void* s2, size_t n)
{
  register const unsigned char *r1 = (const unsigned char *) s1;
  register const unsigned char *r2 = (const unsigned char *) s2;

  while (n && (*r1 == *r2)) {
    ++r1;
    ++r2;
    --n;
  }

  return (n == 0) ? 0 : ((*r1 < *r2) ? -1 : 1);
}

// memset()

void* memset(void* s, int c, size_t n)
{
  register unsigned char *p = (unsigned char *) s;

  /* bcc can optimize the counter if it thinks it is a pointer... */
  register const char *np = (const char *) n;

  while (np) {
    *p++ = (unsigned char) c;
    --np;
  }

  return s;
}
