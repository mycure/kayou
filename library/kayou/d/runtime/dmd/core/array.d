// Written in the D programming language

module runtime.core.array;

class ArrayBoundsError : Error
{
  private:

    uint linnum;
    string filename;

  public:
    this(string filename, uint linnum)
    {
	this.linnum = linnum;
	this.filename = filename;

	/* XXX
	char[] buffer = new char[19 + filename.length + linnum.sizeof * 3 + 1];

	auto len = sprintf(buffer.ptr,
                           "ArrayBoundsError %.*s(%u)", filename, linnum);
        buffer = buffer[0..len];
	*/
	string buffer = "ArrayBoundsError " ~ filename;

	// XXX super(assumeUnique(buffer)); // fine because buffer is unaliased
	super(cast(string)buffer); // fine because buffer is unaliased
    }
}


/********************************************
 * Called by the compiler generated module assert function.
 * Builds an ArrayBoundsError exception and throws it.
 */

extern (C) static void _d_array_bounds(string filename, uint line)
{
    //printf("_d_assert(%s, %d)\n", (char *)filename, line);
    ArrayBoundsError a = new ArrayBoundsError(filename, line);
    //printf("assertion %p created\n", a);
    throw a;
}
