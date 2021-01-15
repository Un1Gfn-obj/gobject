#include <gio/gio.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"

// void ginputstream();
void new_get_set();

int main(){

  g_print("\n");
  // g_print("pid: %d\n",getpid());

  // ginputstream();
  new_get_set();

  return 0;

}
