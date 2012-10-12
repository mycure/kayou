#include "system.h"

// sem

typedef struct _pthread_fastlock
{
  int __status;
  int __spinlock;
} _pthread_fastlock;

typedef struct sem_t
{
  _pthread_fastlock __sem_lock;
  int __sem_value;
  void* __sem_waiting;
} sem_t;

// sem_wait()

int sem_wait(sem_t* sem)
{
  // XXX
}

// sem_init()

int sem_init(sem_t* sem, int pshared, unsigned int value)
{
  // XXX
}

// sem_post()

int sem_post(sem_t* sem)
{
  // XXX
}
