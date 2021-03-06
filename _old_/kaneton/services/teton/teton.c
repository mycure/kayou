/*
 * ---------- header ----------------------------------------------------------
 *
 * project       kaneton
 *
 * license       kaneton
 *
 * file          /home/buckman/kaneton/drivers/cons-simple/cons-simple.c
 *
 * created       matthieu bucchianeri   [sat jun  9 18:36:19 2007]
 * updated       matthieu bucchianeri   [mon sep 10 00:14:07 2007]
 */

#include "teton.h"

/*
 * console instance.
 */

static t_simple_cons	cons = { .vga = 0 };

/*
 * this function scrolls the screen.
 */

static void	       	cons_scroll(t_uint16			lines)
{
  t_uint16		src;
  t_uint16		dst;

  for (src = lines * CONS_COLUMNS * CONS_BPC, dst = 0;
       src < CONS_SIZE;
       src++, dst++)
    {
      cons.vga[dst] = cons.vga[src];

      if ((src >= ((CONS_LINES - lines) * CONS_COLUMNS * CONS_BPC)) &&
	  ((src % 2) == 0))
	{
	  cons.vga[src + 0] = 0;
	  cons.vga[src + 1] = cons.attr;
	}
    }

  cons.line -= lines;
  cons.column = 0;
}

/*
 * the basic print char function.
 */

static int		print_char(char			c)
{
  t_uint16		pos;

  if (cons.line >= CONS_LINES)
    cons_scroll(1);
  if (c == '\n')
    {
      cons.line++;
      cons.column = 0;

      return (1);
    }

  if (c == '\r')
    {
      cons.column = 0;

      return (1);
    }

  if (cons.column >= CONS_COLUMNS)
    {
      cons.column = 0;
      ++cons.line;
      if (cons.line >= CONS_LINES)
	cons_scroll(1);
    }

  pos = cons.line * CONS_COLUMNS * CONS_BPC + cons.column * CONS_BPC;

  cons.vga[pos] = c;
  cons.vga[pos + 1] = cons.attr;

  cons.column++;

  return (1);
}

/*
 * print a string
 */

int			print_string(const char* p)
{
  size_t		i;

  if (cons.vga == 0)
    return (-1);

  for (i = 0; p[i] != '\0'; i++)
    print_char(p[i]);

  return (i - 1);
}

// XXX
int			print_raw(const char* p, unsigned int n)
{
  size_t		i;

  if (cons.vga == 0)
    return (-1);

  for (i = 0; i < n; i++)
    print_char(p[i]);

  return (n);
}

// XXX

void                    cons_clear(void)
{
  t_uint16              i;

  for (i = 0; i < 0xfa0; i++)
    {
      cons.vga[i + 0] = 0;
      cons.vga[i + 1] = cons.attr;
    }

  cons.line = 0;
  cons.column = 0;
}

/*
 * initialize VGA text console and console structure.
 */

int			cons_init(void)
{
  i_region		reg;
  t_uint16		line;
  t_uint16		c;
  int			br;

  if (region_reserve(__as_id,
		     0x1000,
		     CONS_ADDR - 0x1000,
		     REGION_OPT_NONE,
		     0,
		     PAGESZ,
		     &reg) != ERROR_NONE)
    return (-1);

  cons.attr = CONS_FRONT(CONS_WHITE) | CONS_BACK(CONS_BLACK) | CONS_INT;
  cons.vga = (char*)(t_vaddr)reg;
  cons.line = 0;
  cons.column = 0;

  /* XXX[needless with the serial kernel redirection since
     we've got the whole screen for ourselves]
  for (br = 1, line = CONS_LINES - 1; br && line > 0; line--)
    {
      for (c = 0; c < CONS_COLUMNS * CONS_BPC; c += CONS_BPC)
	if (cons.vga[line * CONS_COLUMNS * CONS_BPC + c * CONS_BPC])
	  {
	    br = 0;
	    break;
	  }
    }
  if (line == CONS_LINES - 1)
    {
      cons_scroll(1);
      cons.line = line;
    }
  else
      cons.line = line + 1;
  */

  cons_clear();

  return (0);
}

/*
 * service console requests.
 */

static int		cons_serve(void)
{
  while (1)
    {
      // XXX
    }

  return (0);
}

/*
 * driver's main function.
 */
int			XXXmain(void)
{
  if (cons_init())
    return (-1);

  print_string("[teton] initialised\n");

  return 0;
}

// ----------------------------------------------------------------

typedef void* pthread_mutexattr_t;
typedef void* pthread_mutex_t;
typedef void* sem_t;

void print(const char* msg)
{
  //printf("%s\n", msg);
}

// sem_wait()

int sem_wait(sem_t* sem)
{
  print("[kayou] sem_wait()\n");

  return (0);
}

// sem_init()

int sem_init(sem_t* sem, int pshared, unsigned int value)
{
  print("[kayou] sem_init()\n");

  return (0);
}

// sem_post()

int sem_post(sem_t* sem)
{
  print("[kayou] sem_post()\n");

  return (0);
}

// pthread

typedef unsigned int pthread_t;

// pthread_self()

pthread_t pthread_self()
{
  print("[kayou] pthread_self()\n");

  return 0;
}

// pthread_equal()

int pthread_equal(pthread_t p1, pthread_t p2)
{
  print("[kayou] pthread_equal()\n");

  return p1 == p2;
}

// pthread_mutex_lock()

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
  // XXX print("[kayou] pthread_mutex_lock()\n");

  // XXX[???]

  return (0);
}

// pthread_mutex_unlock()

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
  // XXX print("[kayou] pthread_mutex_unlock()\n");

  // XXX[???]

  return (0);
}

// pthread_mutexattr_init()

int pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
  // XXX print("[kayou] pthread_mutexattr_init()\n");

  // XXX[???]

  return (0);
}

// pthread_mutexattr_destroy()

int pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
  // XXX print("[kayou] pthread_mutexattr_destroy()\n");

  // XXX[???]

  return (0);
}

// pthread_mutexattr_settype()

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type)
{
  // XXX print("[kayou] pthread_mutexattr_settype()\n");

  // XXX[???]

  return (0);
}

// pthread_mutex_init()

int pthread_mutex_init(pthread_mutex_t * mutex,
                       const pthread_mutexattr_t * attr)
{
  // XXX print("[kayou] pthread_mutex_init()\n");

  // XXX[???]

  return (0);
}

// pthread_mutex_destroy()

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
  // XXX print("[kayou] pthread_mutex_destroy()\n");

  // XXX[???]

  return (0);
}
