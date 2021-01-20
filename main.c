#include <glib.h> // g_print()
// #include <unistd.h> // STDIN/OUT/ERR_FILENO

// extern void ginputstream();
// extern void new_get_set();
// extern void method();
// extern void iface();
extern void sig();

int main(){

  g_print("\n");
  // g_print("pid: %d\n",getpid());

  // ginputstream();
  // new_get_set();

  // method();
  // iface();

  sig();

  return 0;

}
