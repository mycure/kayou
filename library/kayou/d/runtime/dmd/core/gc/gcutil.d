
// Copyright (C) 2001-2004 by Digital Mars, www.digitalmars.com
// All Rights Reserved
// Written by Walter Bright

static import runtime.system.system;

/***********************************
 * Map memory.
 */

void *os_mem_map(uint nbytes)
{   void *p;

    p = runtime.system.system.mmap(null, nbytes, runtime.system.system.PROT_READ | runtime.system.system.PROT_WRITE, runtime.system.system.MAP_PRIVATE | runtime.system.system.MAP_ANON, -1, 0);
    return (p == runtime.system.system.MAP_FAILED) ? null : p;
}

/***********************************
 * Commit memory.
 * Returns:
 *	0	success
 *	!=0	failure
 */

int os_mem_commit(void *base, uint offset, uint nbytes)
{
    return 0;
}


/***********************************
 * Decommit memory.
 * Returns:
 *	0	success
 *	!=0	failure
 */

int os_mem_decommit(void *base, uint offset, uint nbytes)
{
    return 0;
}

/***********************************
 * Unmap memory allocated with os_mem_map().
 * Returns:
 *	0	success
 *	!=0	failure
 */

int os_mem_unmap(void *base, uint nbytes)
{
  return runtime.system.system.munmap(base, nbytes);
}


/**********************************************
 * Determine "bottom" of stack (actually the top on x86 systems).
 */

void *os_query_stackBottom()
{
    version (none)
    {	// See discussion: http://autopackage.org/forums/viewtopic.php?t=22
	static void** libc_stack_end;

	if (libc_stack_end == libc_stack_end.init)
	{
	    void* handle = dlopen(null, RTLD_NOW);
	    libc_stack_end = cast(void **)dlsym(handle, "__libc_stack_end");
	    dlclose(handle);
	}
	return *libc_stack_end;
    }
    else
    {	// This doesn't resolve on all versions of Linux
      return runtime.system.system.__libc_stack_end;
    }
}


/**********************************************
 * Determine base address and size of static data segment.
 */

void os_query_staticdataseg(void **base, uint *nbytes)
{
    *base = cast(void *)&runtime.system.system.__data_start;
    *nbytes = cast(byte *)&runtime.system.system._end - cast(byte *)&runtime.system.system.__data_start;
}
