
// real

module runtime.core.typeinfo.ti_real;

static import runtime.core.util.math;

class TypeInfo_e : TypeInfo
{
    override string toString() { return "real"; }

    override hash_t getHash(in void *p)
    {
	return (cast(uint *)p)[0] + (cast(uint *)p)[1] + (cast(ushort *)p)[4];
    }

    static int _equals(real f1, real f2)
    {
	return f1 == f2 ||
		(runtime.core.util.math.isnan(f1) && runtime.core.util.math.isnan(f2));
    }

    static int _compare(real d1, real d2)
    {
	if (d1 !<>= d2)		// if either are NaN
	{
	    if (runtime.core.util.math.isnan(d1))
	    {	if (runtime.core.util.math.isnan(d2))
		    return 0;
		return -1;
	    }
	    return 1;
	}
	return (d1 == d2) ? 0 : ((d1 < d2) ? -1 : 1);
    }

    override int equals(in void *p1, in void *p2)
    {
	return _equals(*cast(real *)p1, *cast(real *)p2);
    }

    override int compare(in void *p1, in void *p2)
    {
	return _compare(*cast(real *)p1, *cast(real *)p2);
    }

    override size_t tsize()
    {
	return real.sizeof;
    }

    override void swap(void *p1, void *p2)
    {
	real t;

	t = *cast(real *)p1;
	*cast(real *)p1 = *cast(real *)p2;
	*cast(real *)p2 = t;
    }

    override void[] init()
    {	static real r;

	return (cast(real *)&r)[0 .. 1];
    }
}

