#include <gio/gio.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"

// External
// extern void ginputstream();
// extern void new_get_set();

static void open_close(){

  ViewerFile *const file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_return_if_fail(file);

  const GError *err=NULL;

  // Low-level
  // g_print("O\n");
  // ((ViewerFileClass*)G_OBJECT_GET_CLASS(file))->open(file,&err);
  // g_print("C\n");
  // ((ViewerFileClass*)G_OBJECT_GET_CLASS(file))->close(file,&err);

  // High-level
  g_print("VFO\n");
  viewer_file_open(file,&err);
  g_print("VFC\n");
  viewer_file_close(file,&err);

}

int main(){

  g_print("\n");
  // g_print("pid: %d\n",getpid());

  // External
  // ginputstream();
  // new_get_set();

  open_close();


  return 0;

}
