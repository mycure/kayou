#include "system.h"

// alloca()

# define alloca(size)   __builtin_alloca (size)

// malloc()

void *malloc(size_t size)
{
  // XXX[temporary since it would be wiser to implement a true allocation algorithm]

  void* result;

  result = mmap((void *) 0, size + sizeof(size_t), PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
  if (result == MAP_FAILED)
    return NULL;
  *(size_t*)result = size;
  return(result + sizeof(size_t));
}

// free()

void free(void *ptr)
{
  // XXX[temporary since it would be wiser to implement a true allocation algorithm]

  ptr -= sizeof(size_t);
  munmap(ptr, * (size_t *) ptr + sizeof(size_t));
}

// realloc()

void *realloc(void *ptr, size_t size)
{
  void *newptr = NULL;

  if (!ptr)
    return malloc(size);
  if (!size) {
    free(ptr);
    return malloc(0);
  }

  newptr = malloc(size);
  if (newptr) {
    size_t old_size = *((size_t *) (ptr - sizeof(size_t)));
    memcpy(newptr, ptr, (old_size < size ? old_size : size));
    free(ptr);
  }
  return newptr;
}


void* calloc(unsigned int nmemb, unsigned int lsize)
{
  void *result;
  unsigned int size=lsize * nmemb;

  /* guard vs integer overflow, but allow nmemb                                                                                                                                                               
   * to fall through and call malloc(0) */
  if (nmemb && lsize != (size / nmemb)) {
    return 0;
  }
  if ((result=malloc(size)) != 0) {
    memset(result, 0, size);
  }
  return result;
}

// mmap()

void* mmap(void* addr, unsigned int len, int prot, int flags, int fd, unsigned int offset)
{
  if (!(flags & MAP_ANONYMOUS))
    return (MAP_FAILED);

  // XXX
  if (map_reserve(_crt_get_as_id(), MAP_OPT_NONE, len, PERM_READ | PERM_WRITE, &addr) != ERROR_NONE)
    return (MAP_FAILED);

  return (void*)addr;
}

// munmap()

int munmap(void* addr, unsigned int len)
{
  return 0;

  // XXX
  //return (map_release(_crt_get_as_id(), (t_vaddr)__addr) == ERROR_NONE ? 0 : -1);
}
