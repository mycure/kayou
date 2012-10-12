// Written in the D programming language

module runtime.core.asserterror;

static import runtime.system.system;

class AssertError : Error
{
    uint linnum;
    char[] filename;

    this(char[] filename, uint linnum)
    {
	this(filename, linnum, null);
    }

    this(char[] filename, uint linnum, char[] msg)
    {
	this.linnum = linnum;
	this.filename = filename;

	char* buffer;
	size_t len;
	int count;

	/* This code is careful to not use gc allocated memory,
	 * as that may be the source of the problem.
	 * Instead, stick with C functions.
	 */

	len = 23 + filename.length + uint.sizeof * 3 + msg.length + 1;
	buffer = cast(char*)runtime.system.system.malloc(len);
	if (buffer is null)
	    super("AssertError no memory");
	else
	{
	  /* XXX
	    version (Win32) alias _snprintf snprintf;
	    count = snprintf(buffer, len, "AssertError Failure %.*s(%u) %.*s",
		filename, linnum, msg);
	    if (count >= len || count == -1)
	    {	super("AssertError internal failure");
		runtime.system.system.free(buffer);
	    }
	    else
            {
                // casting is fine because buffer is unaliased
                auto s = buffer[0 .. count];
		// XXX super(assumeUnique(s));
		super(cast(string)s);
            }
	  */
	  super(cast(string)("AssertError Failure " ~ filename ~ " " ~ msg));
	}
    }

    ~this()
    {
	if (msg.ptr && msg[12] == 'F')	// if it was allocated with malloc()
	{   runtime.system.system.free(cast(char*)msg.ptr);
	    msg = null;
	}
    }
}


/********************************************
 * Called by the compiler generated module assert function.
 * Builds an AssertError exception and throws it.
 */

extern (C) static void _d_assert(char[] filename, uint line)
{
    //printf("_d_assert(%s, %d)\n", cast(char *)filename, line);
    AssertError a = new AssertError(filename, line);
    //printf("assertion %p created\n", a);
    throw a;
}

extern (C) static void _d_assert_msg(char[] msg, char[] filename, uint line)
{
    //printf("_d_assert_msg(%s, %d)\n", cast(char *)filename, line);
    AssertError a = new AssertError(filename, line, msg);
    //printf("assertion %p created\n", a);
    throw a;
}

