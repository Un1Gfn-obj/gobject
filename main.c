#include <gio/gio.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"
#include "./viewer-audio-file.h"

// External
// extern void ginputstream();
// extern void new_get_set();

static void open_close(){

  ViewerFile *const f0=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_print("\n");
  ViewerFile *const fa=g_object_new(VIEWER_TYPE_AUDIO_FILE,NULL);
  const GError *err=NULL;
  g_assert_nonnull(f0);
  g_assert_nonnull(fa);
  g_print("\n");

  // Low-level
  // g_print("O\n");
  // ((ViewerFileClass*)G_OBJECT_GET_CLASS(f0))->open(f0,&err);
  // g_print("C\n");
  // ((ViewerFileClass*)G_OBJECT_GET_CLASS(f0))->close(f0,&err);

  // viewer_file_open(f0,&err);
  // viewer_file_close(f0,&err);

  // viewer_file_open(fa,&err);
  // viewer_file_close(fa,&err);

  viewer_file_close(viewer_file_open(fa,&err),&err);
  g_print("\n");
  viewer_file_close(viewer_file_open(f0,&err),&err);

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
