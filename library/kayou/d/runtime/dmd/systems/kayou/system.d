module runtime.system.system;

// memory layout locations

extern (C)
{
    extern void* __libc_stack_end;
    extern int __data_start;
    extern int _end;
    extern int timezone;

    extern void *_deh_beg;
    extern void *_deh_end;
}

// POSIX calls

const int EXIT_SUCCESS = 0;
const int EXIT_FAILURE = 1;

enum { PROT_NONE = 0, PROT_READ = 1, PROT_WRITE = 2, PROT_EXEC = 4 }
enum { MAP_SHARED = 1, MAP_PRIVATE = 2, MAP_TYPE = 0x0F,
       MAP_FIXED = 0x10, MAP_FILE = 0, MAP_ANONYMOUS = 0x20, MAP_ANON = 0x20 }

const void* MAP_FAILED = cast(void*)-1;

extern (C)
{
  void* memcpy(void* s1, in void* s2, size_t n);
  void* memmove(void* s1, in void* s2, size_t n);
  int memcmp(in void* s1, in void* s2, size_t n);
  void* memset(void* s, int c, size_t n);

  void *alloca(size_t);
  void *malloc(size_t);
  void free(void *);
  void *calloc(size_t, size_t);
  void *realloc(void *, size_t);

  size_t strlen(in char* s);

  void   exit(int);

  void* mmap(void* addr, uint len, int prot, int flags, int fd, uint offset);
  int munmap(void* addr, uint len);
}

// math

extern (C)
{
  double fabs(double x);
}

// sem

struct _pthread_fastlock
{
  int __status;
  int __spinlock;
}

struct sem_t
{
  _pthread_fastlock __sem_lock;
  int __sem_value;
  void* __sem_waiting;
}

extern (C)
{
    int sem_wait(sem_t*);
    int sem_init(sem_t*, int, uint);
    int sem_post(sem_t*);
}

// pthread

alias uint pthread_t;

extern (C)
{
  pthread_t pthread_self();
  int pthread_equal(pthread_t, pthread_t);
}
