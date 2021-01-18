#ifndef __VIEWER_FILE_H__
#define __VIEWER_FILE_H__

#include <glib-object.h>

G_BEGIN_DECLS

// Derivable type
#define VIEWER_TYPE_FILE viewer_file_get_type()
G_DECLARE_DERIVABLE_TYPE(
  ViewerFile,
  viewer_file,
  VIEWER,FILE,
  GObject
)/*
https://developer.gnome.org/gobject/stable/gobject-Type-Information.html#G-DECLARE-DERIVABLE-TYPE:CAPS
G_DECLARE_DERIVABLE_TYPE() does the following:
  GType viewer_file_window_get_type();
  static inline ViewerFile *VIEWER_FILE(gpointer){...} // Type cast
  static inline gboolean VIEWER_IS_FILE(){...}         // Type check
  static inline ViewerFileClass *VIEWER_FILE_CLASS(gpointer){...} // Type cast
  static inline gboolean VIEWER_IS_FILE_CLASS(gpointer){...}      // Type check
  typedef struct _ViewerFileClass ViewerFileClass;
  typedef struct _ViewerFile { GObject parent_instance; } ViewerFile;
*/

// Class structure for derivable type only
struct _ViewerFileClass {

  GObjectClass parent_class;

  // Pure virtfunc prototype
  ViewerFile *((*open)(ViewerFile *const,const GError *const *const));

  // Mere virtfunc prototype
  ViewerFile *((*close)(ViewerFile *const,const GError *const *const));

  // Padding to allow adding up to 12 new virtual functions w/o breaking ABI
  gpointer padding[12];

} ;

// Not yet implemented
// Public nonvirtfunc real prototype
// ViewerFile *viewer_file_new();

// Pure virtfunc redirect prototype
ViewerFile *viewer_file_open(ViewerFile *const,const GError *const *const);

// Mere virtfunc redirect prototype
ViewerFile *viewer_file_close(ViewerFile *const,const GError *const *const);

G_END_DECLS

#endif 
