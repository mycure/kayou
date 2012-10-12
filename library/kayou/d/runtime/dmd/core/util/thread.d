module runtime.core.util.thread;

static import runtime.system.system;

class Thread
{
  runtime.system.system.pthread_t id;

  void* stackBottom;
  void* stackTop;

  enum TS
  {
    INITIAL,        // created
    RUNNING,        // running
    TERMINATED,     // execution finished
    FINISHED        // pthread_join()'ed
  }

  TS getState()
  {
    return state;
  }

  int isSelf()
  {
    //printf("id = %d, self = %d\n", id, pthread_self());
    return runtime.system.system.pthread_equal(runtime.system.system.pthread_self(), id);
  }

  static Thread getThis()
  {
    //printf("getThis(), allThreadsDim = %d\n", allThreadsDim);
    runtime.system.system.pthread_t id = runtime.system.system.pthread_self();

    //printf("id = %d\n", id);
    for (int i = 0; i < allThreadsDim; i++)
      {
	Thread t = allThreads[i];
	//printf("allThreads[%d] = x%x, id = %d\n", i, t, (t ? t.id : 0));
	if (t && runtime.system.system.pthread_equal(id, t.id))
	  {
	    return t;
	  }
      }

    assert(null);
  }

  static Thread[] getAll()
  {
    synchronized (Thread.classinfo) return allThreads[0 .. allThreadsDim];
  }

  // XXX[hack since it was stupidly engineered]
  static void pause()
  {
    pauseHandler();
  }

  // XXX[hack since it was stupidly engineered]
  static void resume()
  {
    resumeHandler();
  }

  static void pauseAll()
  {
    synchronized (Thread.classinfo)
      {
	if (nthreads > 1)
	  {
	    runtime.system.system.pthread_t thisid = runtime.system.system.pthread_self();
	    int npause = 0;

	    for (int i = 0; i < allThreadsDim; i++)
	      {
		Thread t = allThreads[i];

		if (t && !runtime.system.system.pthread_equal(thisid, t.id) && t.state == TS.RUNNING)
		  {
		    pause();

		    /* XXX
                        if (pthread_kill(t.id, SIGUSR1))
                            t.error("cannot pause");
                        else
                            npause++;	// count of paused threads
		    */
		  }
	      }

	    // Wait for each paused thread to acknowledge
	    while (npause--)
	      {
		runtime.system.system.sem_wait(&flagSuspend);
	      }
	  }
      }
  }

  static void resumeAll()
  {
    synchronized (Thread.classinfo)
      {
	if (nthreads > 1)
	  {
	    runtime.system.system.pthread_t thisid = runtime.system.system.pthread_self();

	    for (int i = 0; i < allThreadsDim; i++)
	      {
		Thread t = allThreads[i];

		if (t && t.id != thisid && t.state == TS.RUNNING)
		  t.resume();
	      }
	  }
      }
  }

  static uint nthreads = 1;

private:

  static uint allThreadsDim;

  // Set max to Windows equivalent for compatibility.
  // pthread_create will fail gracefully if stack limit
  // is reached prior to allThreads max.
  static Thread[0x400] allThreads;

  static runtime.system.system.sem_t flagSuspend;

  TS state;
  int idx = -1;			// index into allThreads[]
  int flags = 0;

  /**************************************
   * Create a Thread for global main().
   */

  public static void thread_init()
  {
    Thread t = new Thread();

    t.state = TS.RUNNING;
    t.id = runtime.system.system.pthread_self();

    t.stackBottom = cast(void*)runtime.system.system.__libc_stack_end;

    assert(!allThreads[0]);
    allThreads[0] = t;
    allThreadsDim = 1;
    t.idx = 0;

    int result;

    result = runtime.system.system.sem_init(&flagSuspend, 0, 0);
    if (result)
      assert(null);
  }

  static void pauseHandler()
  {
    int result;

    // Save all registers on the stack so they'll be scanned by the GC
    asm
      {
	pusha	;
      }

    Thread t = getThis();

    t.stackTop = getESP();
    t.flags &= ~1;

    // Release the semaphore _after_ stackTop is set
    runtime.system.system.sem_post(&flagSuspend);

    while (1)
      {
	// XXX[ugly hack since it spins freely until resumed :( but no time to do better]
	if (t.flags & 1)		// ensure it was resumeHandler()
	  break;
      }

    // Restore all registers
    asm
      {
	popa	;
      }
  }

  static void resumeHandler()
  {
    Thread t = getThis();

    t.flags |= 1;
  }

  public static void* getESP()
  {
    asm
      {   naked	;
	mov EAX,ESP	;
	ret		;
      }
  }
}
