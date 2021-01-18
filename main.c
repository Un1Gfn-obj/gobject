#include <gio/gio.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"
#include "./viewer-audio-file.h"
#include "./viewer-editable.h"
#include "./viewer-editable-lossy.h"

// External
// extern void ginputstream();
// extern void new_get_set();

/*static void open_close(){

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

  // g_object_unref(f0);
  // g_object_unref(fa);

}*/

static void iface(){

  ViewerFile *const vf=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_print("\n");

  GError *e=NULL;
  viewer_editable_save(VIEWER_EDITABLE(vf),&e);
  viewer_editable_undo(VIEWER_EDITABLE(vf),1);
  viewer_editable_redo(VIEWER_EDITABLE(vf),1);
  viewer_editable_lossy_compress(VIEWER_EDITABLE_LOSSY(vf));
  g_print("\n");

  ViewerFile *const vaf=g_object_new(VIEWER_TYPE_AUDIO_FILE,NULL);
  g_print("\n");

  viewer_editable_save(VIEWER_EDITABLE(vaf),&e);
  viewer_editable_undo(VIEWER_EDITABLE(vaf),1);
  viewer_editable_redo(VIEWER_EDITABLE(vaf),1);
  viewer_editable_lossy_compress(VIEWER_EDITABLE_LOSSY(vaf));
  g_print("\n");

  g_object_unref(vf);
  g_print("\n");

  g_object_unref(vaf);
  g_print("\n");

}

int main(){

  g_print("\n");
  // g_print("pid: %d\n",getpid());

  // External
  // ginputstream();
  // new_get_set();

  // open_close();

  iface();

  return 0;

}
