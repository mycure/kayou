// Written in the D programming language

/**
 * Macros:
 *	WIKI=Phobos/StdOutOfMemory
 * Copyright:
 *	Placed into public domain.
 *	www.digitalmars.com
 */

module runtime.core.memory;

/******
 * This exception is thrown when out of memory errors happen.
 */

class OutOfMemoryException : Exception
{
    static string s = "Out of memory";

    /**
     * Default constructor
     */
    this()
    {
	super(s);
    }

    override string toString()
    {
	return s;
    }
}

extern (C) void _d_OutOfMemory()
{
    throw cast(OutOfMemoryException)
	  cast(void *)
	  OutOfMemoryException.classinfo.init;
}

static this()
{
}
