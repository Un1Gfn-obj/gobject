# https://developer.gnome.org/gobject/2.66/

default: main.out;

MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

CC:=gcc

# https://developer.gnome.org/glib/stable/glib-Version-Information.html
# https://developer.gnome.org/glib/stable/glib-compiling.html
CFLAGS:=\
-std=gnu11 -g -O0 -Wall -Wextra -Wno-unused-parameter -Winline -Wdeprecated-declarations \
$(shell pkg-config --cflags gobject-2.0,gio-unix-2.0) \
-DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_66 \
-DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_66

LDLIBS:=$(shell pkg-config --libs gobject-2.0,gio-unix-2.0)

# %.s: %.c ; $(CC) -S $(PRIMFLAGS) -o $@ $<
# function_foo.s:

# function_foo.o: function_foo.c; $(CC) -c $(PRIMFLAGS) -o $@ $<
# make -B function_foo.o && objdump -d function_foo.o

%.check: % ; $(CC) $(CFLAGS) -fsyntax-only $<
viewer-file.h.check:
viewer-file.c.check:

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
