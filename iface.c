// Objects
#include "./viewer-file.h"
#include "./viewer-audio-file.h"

// Interfaces
#include "./viewer-editable.h"
#include "./viewer-editable-lossy.h"

void iface(){

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

  GValue af=G_VALUE_INIT;
  g_value_init(&af,G_TYPE_DOUBLE);

  g_object_get_property(G_OBJECT(vf),"autosave-frequency",&af);
  g_print("autosave-frequency=%lf\n",g_value_get_double(&af));
  g_print("\n");

  g_value_set_double(&af,89.64);
  g_object_set_property(G_OBJECT(vf),"autosave-frequency",&af);
  g_object_get_property(G_OBJECT(vf),"autosave-frequency",&af);
  g_print("autosave-frequency=%lf\n",g_value_get_double(&af));
  g_print("\n");

  g_object_unref(vf);
  g_print("\n");

  g_object_unref(vaf);
  g_print("\n");

}
