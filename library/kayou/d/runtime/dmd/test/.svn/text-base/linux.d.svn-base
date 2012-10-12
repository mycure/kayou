import runtime.core.compiler;
import runtime.core.os;

class Test
{
  int value = 5;

  invariant()
  {
    printf("[kayou] invariant checking\n");

    assert(this.value < 10);

    printf("XXX ... %d\n", this.value);
  }

  void Teton(int v)
  {
    printf("[kayou] Teton()\n");

    this.value = v;
  }
}

import kaneton;

int main(invariant(char[][]) args)
{
  string teton;

  // XXX
  kaneton.Map.Reserve(0, 0, 0, 0, 0);

  teton = "program(" ~ args[0] ~ ") ... ";

    int a[];
    a.reverse;				// adi
    a.sort;				// qsort

    printf("args.length = %d\n", args.length);
    for (int i = 0; i < args.length; i++)
	printf("args[%d] = '%s'\n", i, cast(char *)args[i]);

    int[3] x;
    x[0] = 3;
    x[1] = 45;
    x[2] = -1;
    x.sort;
    assert(x[0] == -1);
    assert(x[1] == 3);
    assert(x[2] == 45);

    foreach_reverse (dchar d; "hello"c) { ; }
    foreach_reverse (k, dchar d; "hello"c) { ; }

    long u = 999;
    long v = 333;

    double d = 3.0;

    printf("%u\n", u / v);

    int z[100] = 42;

    printf("%u\n", z[21]);

    printf("[compiler version] %u.%u\n", version_major, version_minor);

    printf("[system endianness] %d\n", endian);
    printf("[system family] %d\n", family);

    synchronized
    {
      printf("here\n");
    }

    // ---

    {
      Test test = new Test;
    }

    creal aa = cast(creal)5; // a = 5 + 0i
    ireal bb = 7i; // b = 7i
    auto cc = aa + bb + 7i; // c = 5 + 14i
    cc = (6 + 2i - 1 + 3i) / 3i;

    {
      int[] A = [ 1, 2 ];

      printf("HERE\n");
      A.reverse;

      int[] B = A[];

      int[] C = A[] ~ B[];
    }

    printf("Success!\n");

  return (0);
}
