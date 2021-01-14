# https://developer.gnome.org/gobject/2.66/

default: main.out;

MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

CC:=gcc

CFLAGS:=-std=gnu11 -g -O0 -Wall -Wextra -Wno-unused-parameter -Winline $(shell pkg-config --cflags gobject-2.0,gio-unix-2.0) # -fmax-errors=1

LDLIBS:=$(shell pkg-config --libs gobject-2.0,gio-unix-2.0)

# %.s: %.c ; $(CC) -S $(PRIMFLAGS) -o $@ $<
# function_foo.s:

# function_foo.o: function_foo.c; $(CC) -c $(PRIMFLAGS) -o $@ $<
# make -B function_foo.o && objdump -d function_foo.o

# %.check: % ; $(CC) $(CFLAGS) -fsyntax-only $<
# viewer-file.h.check:

# %.o: %.c ; $(CC) -c $(CFLAGS) -o $@ $<
# viewer-file.o:

main.out: main.c viewer-file.c viewer-file.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(filter %.c , $^ ) $(LDLIBS)

%.i: %.c; $(CC) -E $(CFLAGS) -o $@ $<
viewer-file.i:

clean:
	@rm -fv *.s *.o *.out *.i # *.h.gch

# https://developer.gnome.org/glib/stable/glib-running.html
# env G_ENABLE_DIAGNOSTIC=1 derivable.out
