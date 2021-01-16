#include <gio/gio.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"

// External
// extern void ginputstream();
// extern void new_get_set();

static void methods(){

  ViewerFile *const file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_assert(file);

  const GError *err=NULL;
  viewer_file_open(file,&err);
  g_assert_no_error(err);
  viewer_file_close(file,&err);
  g_assert_no_error(err);
  g_print("\n");

  g_object_set(G_OBJECT(file),
    "filename","/tmp/log",
  NULL);
  viewer_file_open(file,&err);
  g_assert_no_error(err);
  viewer_file_close(file,&err);
  g_assert_no_error(err);
  g_print("\n");

  g_object_set(G_OBJECT(file),
    "filename","",
  NULL);
  viewer_file_open(file,&err);
  g_assert_no_error(err);
  viewer_file_close(file,&err);
  g_assert_no_error(err);
  g_print("\n");

  g_object_set(G_OBJECT(file),
    "filename","file:///var/log",
  NULL);
  viewer_file_open(file,&err);
  g_assert_no_error(err);
  viewer_file_close(file,&err);
  g_assert_no_error(err);
  g_print("\n");

  g_object_set(G_OBJECT(file),
    "filename","https://example.org/",
  NULL);
  viewer_file_open(file,&err);
  g_assert_no_error(err);
  viewer_file_close(file,&err);
  g_assert_no_error(err);
  g_print("\n");

}

int main(){

  g_print("\n");
  // g_print("pid: %d\n",getpid());

  // External
  // ginputstream();
  // new_get_set();

  methods();

  return 0;

}
