LIB=$(OBJDIR)/libkayou.a
LINK=$(shell basename $(LIB))

CC=gcc
DMD=dmd

CFLAGS=-m32 -O -nostdinc -nostdlib
DFLAGS=-release -O -unittest
OBJDIR=obj/release

RM=rm -f

# core

CORE_D := $(wildcard core/*.d)
CORE_C := core/complex.c core/critical.c core/monitor.c #$(wildcard core/*.c) - deh.c

CORE_GC_D := $(wildcard core/gc/*.d)
CORE_GC_C := $(wildcard core/gc/*.c)

CORE_TYPEINFO_D := $(wildcard core/typeinfo/*.d)
CORE_TYPEINFO_C := $(wildcard core/typeinfo/*.c)

CORE_UTIL_D := $(wildcard core/util/*.d)
CORE_UTIL_C := $(wildcard core/util/*.c)

# system

SYSTEM_D := $(wildcard system/*.d)
SYSTEM_C := $(wildcard system/*.c)

# objects

OBJS := $(CORE_D:.d=.o) $(CORE_C:.c=.o) \
	$(CORE_GC_D:.d=.o) $(CORE_GC_C:.c=.o) \
	$(CORE_TYPEINFO_D:.d=.o) $(CORE_TYPEINFO_C:.c=.o) \
	$(CORE_UTIL_D:.d=.o) $(CORE_UTIL_C:.c=.o) \
	$(SYSTEM_D:.d=.o) $(SYSTEM_C:.c=.o)

OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

.SUFFIXES: .d

%:
	rm -f system
	ln -s systems/$@ system
	make main

main: $(LIB)
	ln -sf $(LIB)

$(LIB) : $(OBJS)
	rm -f $(LIB)
	ar -r $@ $(OBJS)

clear:
	$(RM) $(LINK)
	$(RM) -R obj/

clean:	clear
	rm -f system

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.d
	$(DMD) -I$(dir $<) -c $(DFLAGS) -of$@ $<
