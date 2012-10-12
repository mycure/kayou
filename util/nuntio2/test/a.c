#include "a.h"
#include "../lib-c/archive.h"

int main()
{
  teton t;
  teton u;

  t.bande = 42;
  t.suce = 128;

  t_nuntio_archive a;

  a.offset = 0;

  nuntio_teton_serialize(&t, &a);

  a.offset = 0;

  nuntio_teton_extract(&a, &u);

  printf("[suce] %d [bande] %d\n", u.suce, u.bande);
}

