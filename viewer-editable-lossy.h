#ifndef __VIEWER_EDITABLE_LOSSY_H__
#define __VIEWER_EDITABLE_LOSSY_H__

#include "./viewer-editable.h"

G_BEGIN_DECLS

#define VIEWER_TYPE_EDITABLE_LOSSY viewer_editable_lossy_get_type()
G_DECLARE_INTERFACE(
  ViewerEditableLossy, // Name of the new type
  viewer_editable_lossy,
  VIEWER,
  EDITABLE_LOSSY,
  ViewerEditable // Name of the prerequisite type for the interface
)/*
G_DECLARE_INTERFACE() does the following:
  [Please refer to viewer-editable.h]
*/

struct _ViewerEditableLossyInterface{
  ViewerEditableInterface parent_iface;
  void (*compress)(ViewerEditableLossy *const);
};

void viewer_editable_lossy_compress(ViewerEditableLossy *const);

G_END_DECLS

#endif
