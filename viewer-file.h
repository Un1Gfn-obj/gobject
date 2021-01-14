// https://developer.gnome.org/gobject/2.66/howto-gobject.html#howto-gobject-header

#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

// Type
#define VIEWER_TYPE_FILE viewer_file_get_type()
G_DECLARE_FINAL_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)
// G_DECLARE_DERIVABLE_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)

struct _ViewerFileClass {

  GObjectClass parent_class;

  // Class virtual function fields.
  // declare open as pointer to function (ViewerFile*, GError**) returning void
  void(*open)(ViewerFile*,GError**);

  // Padding to allow adding up to 12 new virtual functions w/o breaking ABI
  gpointer padding[12];

};

// Methods
ViewerFile *viewer_file_new();
void viewer_file_open(ViewerFile *const,GError *const *const);

G_END_DECLS

#endif 
