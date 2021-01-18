#ifndef __VIEWER_EDITABLE_H__
#define __VIEWER_EDITABLE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define VIEWER_TYPE_EDITABLE viewer_editable_get_type()
G_DECLARE_INTERFACE(
  ViewerEditable, // Name of the new type
  viewer_editable,
  VIEWER,
  EDITABLE,
  GObject // Name of the prerequisite type for the interface
)/*
https://developer.gnome.org/gobject/2.66/gobject-Type-Information.html#G-DECLARE-INTERFACE:CAPS
G_DECLARE_INTERFACE() does the following:
  GType viewer_editable_get_type();
  typedef struct _ViewerEditableInterface ViewerEditableInterface;
  static inline ViewerEditable *VIEWER_EDITABLE(gpointer){...}    // Type cast
  static inline gboolean VIEWER_IS_EDITABLE(gpointer){...}        // Type check
  static inline ViewerEditableInterface *VIEWER_EDITABLE_GET_IFACE(gpointer){...}
*/

struct _ViewerEditableInterface{
  GTypeInterface parent_iface;
  void (*save)(ViewerEditable *const,GError *const *const);
  void (*undo)(ViewerEditable *const,const guint);
  void (*redo)(ViewerEditable *const,const guint);
};

void viewer_editable_save(ViewerEditable *const,GError *const *const);
void viewer_editable_undo(ViewerEditable *const,const guint);
void viewer_editable_redo(ViewerEditable *const,const guint);

G_END_DECLS

#endif
