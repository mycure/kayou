
/**
 ** Auto-generated file, dont modify directly
 ** your changes will be lost !
 **
 ** Generated by DSX on 2006-04-12 16:13:48.073080
 ** by unknown@callisto
 **/

#include <libc.h>
#include "pthread.h"
#include "tg_proto.h"

struct thargs {
	pthread_t thread;
	tg_args_t *args;
};

extern pthread_barrier_t	barrier;

static void* tg_thread( void *_args )
{
	struct thargs *args = _args;

	printf("tg ready\n");

	pthread_barrier_wait(&barrier);

	printf("tg args = %p\n", args);

	while (1)
	  tg_func_tg( args->args );
	return NULL;
}

pthread_t tg_launcher( tg_args_t *args )
{
  static struct thargs thargs;
  thargs.args = args;
  pthread_create( &(thargs.thread), NULL, tg_thread, &thargs );
  return thargs.thread;
}
