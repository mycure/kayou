module runtime.core.util.math;

int isnan(real e)
{
  ushort* pe = cast(ushort *)&e;
  ulong*  ps = cast(ulong *)&e;

  return (pe[4] & 0x7FFF) == 0x7FFF &&
    *ps & 0x7FFFFFFFFFFFFFFF;
}
