clear:
	rm -f linux kayou *.o *~

linux:
	dmd -I. -I.. -I../../../kayou  -L-L../ -c linux.d -oflinux.o
	gcc linux.o -o linux -m32 -Xlinker -L../ -lkayou -lpthread -lrt

test:
	dmd -I. -I.. -I../../../kayou -L-L../ -c test.d -oftest.o

kayou:
	dmd -I. -I.. -I../../../kayou -L-L../ -c kayou.d -ofkayou.o
	gcc -nostdinc -nostdlib -c _crt.S -o _crt.o
	gcc -nostdinc -nostdlib -c _kayou.c -o _kayou.o
	gcc -nostdinc -nostdlib _crt.o _kayou.o kayou.o -o kayou -m32 -Xlinker -L../ -lkayou
