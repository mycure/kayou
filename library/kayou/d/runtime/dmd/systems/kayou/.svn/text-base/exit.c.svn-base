#include "system.h"

// atexit

#define ATEXIT_MAX 4

typedef void (*__atexit_function) (void);

__atexit_function __atexit_function_table[ATEXIT_MAX];
unsigned int __atexit_count = 0;

pthread_mutex_t __atexit_lock = PTHREAD_MUTEX_INITIALIZER;

int atexit(void (*func)(void))
{
  struct __atexit_function *efp;

  if (func == NULL) {
    return 0;
  }

  pthread_mutex_lock(&__atexit_lock);

  if (__atexit_count >= ATEXIT_MAX) {
    pthread_mutex_unlock(&__atexit_lock);
    return 1;
  }

  __atexit_function_table[__atexit_count++] = func;

  pthread_mutex_unlock(&__atexit_lock);

  return 0;
}

// exit()

__attribute__ ((__noreturn__)) void exit(int status)
{
  int i;

  for (i = 0; i < __atexit_count; i++)
    __atexit_function_table[i]();

  while (1); // XXX[should call kayou.task_exit()]
}
