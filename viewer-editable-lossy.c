#include "./viewer-editable.h"
#include "./viewer-editable-lossy.h"

/* Make the ViewerEditableLossy interface require ViewerEditable interface. */
G_DEFINE_INTERFACE(
  ViewerEditableLossy, // Name of the new type
  viewer_editable_lossy,
  VIEWER_TYPE_EDITABLE // GType of the prerequisite type for the interface
)/*
G_DEFINE_INTERFACE() does the following:
  [Please refer to viewer-editable.c]
*/

static void viewer_editable_lossy_default_init(ViewerEditableLossyInterface *iface){
  // add properties and signals to the interface here
  g_print("viewer_editable_lossy_default_init()\n");
}

void viewer_editable_lossy_compress(ViewerEditableLossy *const self){
  g_assert(VIEWER_IS_EDITABLE_LOSSY(self));
  ViewerEditableLossyInterface *const iface=VIEWER_EDITABLE_LOSSY_GET_IFACE(self);
  g_assert_nonnull(iface->compress);
  iface->compress(self);
}
