# https://developer.gnome.org/gobject/2.66/

default: main.out;

MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

CC:=gcc

              INC:=$(shell pkg-config --cflags-only-I gobject-2.0,gio-unix-2.0)
CFLAGS:=$(INC) $(shell pkg-config --cflags-only-other gobject-2.0,gio-unix-2.0)

# https://developer.gnome.org/glib/stable/glib-Version-Information.html
# https://developer.gnome.org/glib/stable/glib-compiling.html
CFLAGS:=\
-std=gnu11 -g -O0 -Wall -Wextra -Wno-unused-parameter -Winline -Wdeprecated-declarations \
$(CFLAGS) \
-DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_66 \
-DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_66

LDLIBS:=$(shell pkg-config --libs gobject-2.0,gio-unix-2.0)

# %.s: %.c ; $(CC) -S $(PRIMFLAGS) -o $@ $<
# function_foo.s:

# function_foo.o: function_foo.c; $(CC) -c $(PRIMFLAGS) -o $@ $<
# make -B function_foo.o && objdump -d function_foo.o

%.check: % ; $(CC) $(CFLAGS) -fsyntax-only $<
# viewer-file.h.check:
# viewer-file.c.check:

%.i: % ; $(CC) -E $(CFLAGS) -o $@ $<
# viewer-file.h.i:

# %.o: %.c ; $(CC) -c $(CFLAGS) -o $@ $<
# viewer-file.o:

main.out: ginputstream.c new-get-set.c main.c $(foreach i, \
  viewer-file viewer-audio-file viewer-editable viewer-editable-lossy, \
$(foreach j, \
  c h, \
$(i).$(j)))
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(filter %.c , $^ ) $(LDLIBS)

clean: 
	@rm -fv *.s *.o *.out *.i # *.h.gch

cscope:
	cscope $(INC) -1 $(id) $(file)

# https://developer.gnome.org/glib/stable/glib-running.html
# env G_ENABLE_DIAGNOSTIC=1 derivable.out
