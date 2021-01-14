// https://developer.gnome.org/gobject/2.66/ch01s02.html

static void function_foo(const int);

static void function_bar(){
  function_foo(0xaaaaaaa);
}

static void function_foo(const int foo){}
