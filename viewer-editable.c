#include "./viewer-editable.h"

G_DEFINE_INTERFACE(
  ViewerEditable, // name of the new type
  viewer_editable,
  G_TYPE_OBJECT // GType of the prerequisite type for the interface
)/*
https://developer.gnome.org/gobject/stable/gobject-Type-Information.html#G-DEFINE-INTERFACE:CAPS
G_DEFINE_INTERFACE() does the following:
  static void viewer_editable_default_init(ViewerEditableInterface*);
  GType viewer_editable_get_type(){...}
*/

static void viewer_editable_default_init(ViewerEditableInterface *iface){
  // add properties and signals to the interface here
  g_print("viewer_editable_default_init()\n");
}

void viewer_editable_save(ViewerEditable *const self,GError *const *const error){
  g_assert(
    VIEWER_IS_EDITABLE(self) &&
    (error == NULL || *error == NULL)
  );
  ViewerEditableInterface *const iface=VIEWER_EDITABLE_GET_IFACE(self);
  g_assert_nonnull(iface->save);
  iface->save(self, error);
}

void viewer_editable_undo(ViewerEditable *const self,const guint n_steps){
  g_assert(VIEWER_IS_EDITABLE(self));
  ViewerEditableInterface *const iface=VIEWER_EDITABLE_GET_IFACE(self);
  g_assert_nonnull(iface->undo);
  iface->undo(self,n_steps);
}

void viewer_editable_redo(ViewerEditable *const self,const guint n_steps){
  g_assert(VIEWER_IS_EDITABLE(self));
  ViewerEditableInterface *const iface=VIEWER_EDITABLE_GET_IFACE(self);
  g_assert_nonnull(iface->redo);
  iface->redo(self,n_steps);
}
