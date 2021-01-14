// https://developer.gnome.org/gobject/2.66/howto-gobject-code.html

#include "./viewer-file.h"

// derivable: private data should be in private structure
// Private structure "ViewerFilePrivate"
typedef struct {
  // private data for derivable
  gchar *filename;
} ViewerFilePrivate;

// final: private data should be in instance structure
#ifdef F
// Instance structure "ViewerFile"
struct _ViewerFile {
  GObject parent_instance;
  // private data for final
  // ...
};
#endif

#ifdef D
// Both ok for derivable types
// G_DEFINE_TYPE(ViewerFile,viewer_file,G_TYPE_OBJECT)
G_DEFINE_TYPE_WITH_PRIVATE(ViewerFile,viewer_file,G_TYPE_OBJECT)
#elif defined F
// Final types do not need private data
G_DEFINE_TYPE(ViewerFile,viewer_file,G_TYPE_OBJECT)
#else
#error
#endif
