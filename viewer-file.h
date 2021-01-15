// https://developer.gnome.org/gobject/2.66/howto-gobject.html#howto-gobject-header

#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

// Derivable type
#define VIEWER_TYPE_FILE viewer_file_get_type()
G_DECLARE_DERIVABLE_TYPE(ViewerFile,viewer_file,VIEWER,FILE,GObject)

// Class structure for derivable type only
typedef struct _ViewerFileClass {

  GObjectClass parent_class;

  // Mere virtfunc prototype
  ViewerFile *((*close)(ViewerFile *const,const GError *const *const));
  // Mere virtfunc prototype (private)
  gboolean (*can_memory_map)(ViewerFile *self);

  // Padding to allow adding up to 12 new virtual functions w/o breaking ABI
  gpointer padding[12];

} ViewerFileClass;

// Public nonvirtfunc real prototype
ViewerFile *viewer_file_new();
// Public nonvirtfunc real prototype
ViewerFile *viewer_file_open(ViewerFile *const,const GError *const *const);
// Mere virtfunc redirect prototype
ViewerFile *viewer_file_close(ViewerFile *const,const GError *const *const);

G_END_DECLS

#endif 
