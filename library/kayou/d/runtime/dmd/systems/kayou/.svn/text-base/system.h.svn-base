#ifndef RUNTIME_SYSTEM_SYSTEM_H
#define RUNTIME_SYSTEM_SYSTEM_H

// basic definitions and types

typedef unsigned int u_int32_t;
typedef signed int int32_t;

typedef unsigned int size_t;

#define NULL ((void*)0)

// math

double fabs(double);
double sqrt(double);

// POSIX calls

void *calloc(size_t, size_t);

// assert

// XXX
#define assert(expr) \
  { \
  int _i_; \
  if (!(expr)) \
    _i_ = 123 / 0; \
  }

// pthread_mutex

#define __SIZEOF_PTHREAD_MUTEX_T 24
#define __SIZEOF_PTHREAD_MUTEXATTR_T 4

# define PTHREAD_MUTEX_INITIALIZER \
  { { 0, 0, 0, 0, 0, { 0 } } }

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;

typedef union
{
  struct __pthread_mutex_s
  {
    int __lock;
    unsigned int __count;
    int __owner;
    /* KIND must stay at this position in the structure to maintain
       binary compatibility.  */
    int __kind;
    unsigned int __nusers;
    __extension__ union
    {
      int __spins;
      __pthread_slist_t __list;
    };
  } __data;
  char __size[__SIZEOF_PTHREAD_MUTEX_T];
  long int __align;
} pthread_mutex_t;

typedef union
{
  char __size[__SIZEOF_PTHREAD_MUTEXATTR_T];
  long int __align;
} pthread_mutexattr_t;

enum
  {
    PTHREAD_MUTEX_TIMED_NP,
    PTHREAD_MUTEX_RECURSIVE_NP,
    PTHREAD_MUTEX_ERRORCHECK_NP,
    PTHREAD_MUTEX_ADAPTIVE_NP
  };

int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutexattr_init(pthread_mutexattr_t *);
int pthread_mutexattr_settype(pthread_mutexattr_t *, int);
int pthread_mutexattr_destroy(pthread_mutexattr_t *);
int pthread_mutex_init(pthread_mutex_t *,
		       const pthread_mutexattr_t *);
int pthread_mutex_destroy(pthread_mutex_t *);

// atexit

int atexit(void (*)(void));

// memory

enum { PROT_NONE = 0, PROT_READ = 1, PROT_WRITE = 2, PROT_EXEC = 4 };
enum { MAP_SHARED = 1, MAP_PRIVATE = 2, MAP_TYPE = 0x0F,
       MAP_FIXED = 0x10, MAP_FILE = 0, MAP_ANONYMOUS = 0x20, MAP_ANON = 0x20 };

#define MAP_FAILED ((void*)-1)

void *malloc(size_t);
void* mmap(void*, unsigned int, int, int, int, unsigned int);

// data

void* memset(void*, int, size_t);
void* memcpy(void*, void*, unsigned int);

#endif
