// https://developer.gnome.org/gobject/2.66/howto-gobject.html#howto-gobject-header

#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

// Derivable type
#define VIEWER_TYPE_FILE viewer_file_get_type()
G_DECLARE_DERIVABLE_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)

// Class structure for derivable type
typedef struct _ViewerFileClass {
  GObjectClass parent_class;
  // Class virtual function fields.
  ViewerFile *((*open)(ViewerFile*,GError**));
  // Padding to allow adding up to 12 new virtual functions w/o breaking ABI
  gpointer padding[12];
} ViewerFileClass;

// Public methods
ViewerFile *viewer_file_new();
ViewerFile *viewer_file_open(ViewerFile *const,const GError *const *const);

G_END_DECLS

#endif 
