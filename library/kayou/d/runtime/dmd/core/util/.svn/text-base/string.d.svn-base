module runtime.core.util.string;

static import runtime.system.system;

invariant(char[10]) digits = "0123456789";

int compare(in char[] s1, in char[] s2)
{
    auto len = s1.length;
    int result;

    //printf("cmp('%.*s', '%.*s')\n", s1, s2);
    if (s2.length < len)
	len = s2.length;
    result = runtime.system.system.memcmp(s1.ptr, s2.ptr, len);
    if (result == 0)
	result = cast(int)s1.length - cast(int)s2.length;
    return result;
}

string convert(uint u)
{   char[uint.sizeof * 3] buffer = void;
    int ndigits;
    char[] result;

    ndigits = 0;
    if (u < 10)
	// Avoid storage allocation for simple stuff
	return digits[u .. u + 1];
    else
    {
	while (u)
	{
	    uint c = (u % 10) + '0';
	    u /= 10;
	    ndigits++;
	    buffer[buffer.length - ndigits] = cast(char)c;
	}
	result = new char[ndigits];
	result[] = buffer[buffer.length - ndigits .. buffer.length];
    }
    // XXX return assumeUnique(result);
    return cast(string)result;
}
