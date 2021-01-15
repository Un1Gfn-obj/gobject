// https://developer.gnome.org/gobject/2.66/howto-gobject.html#howto-gobject-header

#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define VIEWER_TYPE_FILE viewer_file_get_type()

// Final type
G_DECLARE_FINAL_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)

// No ViewerFileClass for final type

// Public methods
ViewerFile *viewer_file_new();
ViewerFile *viewer_file_open(ViewerFile *const,const GError *const *const);

G_END_DECLS

#endif 
