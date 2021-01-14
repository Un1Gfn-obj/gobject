
```bash
cscope $(pkg-config --cflags gobject-2.0,gio-unix-2.0) -1 _GTypeInfo viewer-file.h
cscope $(pkg-config --cflags gobject-2.0,gio-unix-2.0) -1 GObjectClass viewer-file.h
cscope $(pkg-config --cflags gobject-2.0,gio-unix-2.0) -1 _GParamSpec viewer-file.c
```
