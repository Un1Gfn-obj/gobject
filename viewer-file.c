// https://developer.gnome.org/gobject/2.66/howto-gobject-code.html

#include <gio/gio.h> // GInputStream
#include "./viewer-file.h"
#include "./def.h"

// Private structure
#ifdef P
typedef struct _ViewerFilePrivate {
  // Private data for derivable (impossible for final?)
  GInputStream *input_stream;
} ViewerFilePrivate;
#endif

// Instance structure
typedef struct _ViewerFile {
  GObject parent_instance;
  // Public data for derivable or final
  gchar *filename; // Public
  guint zoom_level; // Public
} ViewerFile;

#ifdef D
// Both ok for derivable types
// G_DEFINE_TYPE(ViewerFile,viewer_file,G_TYPE_OBJECT) // Remove ViewerFilePrivate
G_DEFINE_TYPE_WITH_PRIVATE(ViewerFile,viewer_file,G_TYPE_OBJECT) // Keep ViewerFilePrivate
#elif defined F
G_DEFINE_TYPE(ViewerFile,viewer_file,G_TYPE_OBJECT) // Remove ViewerFilePrivate
#else
#error
#endif

static void viewer_file_dispose(GObject *const gobject){
  ViewerFilePrivate *const priv=viewer_file_get_instance_private(VIEWER_FILE(gobject));
  /* In dispose(), you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a 
   * reference.
   */
  /* dispose() might be called multiple times, so we must guard against
   * calling g_object_unref() on an invalid GObject by setting the member
   * NULL; g_clear_object() does this for us.
   */
  g_clear_object(&(priv->input_stream));
  /* Always chain up to the parent class; there is no need to check if
   * the parent class implements the dispose() virtual function: it is
   * always guaranteed to do so
   */
  G_OBJECT_CLASS(viewer_file_parent_class)->dispose(gobject);
}

static void viewer_file_finalize(GObject *const gobject){
  ViewerFilePrivate *const priv=viewer_file_get_instance_private(VIEWER_FILE(gobject));
  g_free(priv->filename);
  /* Always chain up to the parent class; as with dispose(), finalize()
   * is guaranteed to exist on the parent's class virtual function table
   */
  G_OBJECT_CLASS(viewer_file_parent_class)->finalize(gobject);
}

typedef enum _ViewerFileProperty {
  PROP_FILENAME = 1,
  PROP_ZOOM_LEVEL,
  N_PROPERTIES
} ViewerFileProperty;

static GParamSpec *obj_properties[N_PROPERTIES]={};

static void viewer_file_set_property(
  GObject *const object,
  const guint property_id,
  const GValue *const value,
  GParamSpec *const pspec
){
  ViewerFile *self=VIEWER_FILE(object);
  switch((ViewerFileProperty)property_id){
  case PROP_FILENAME:
    g_free(self->filename);
    self->filename=g_value_dup_string(value);
    g_print("filename: %s\n", self->filename);
    break;
  case PROP_ZOOM_LEVEL:
    self->zoom_level = g_value_get_uint(value);
    g_print("zoom level: %u\n", self->zoom_level);
    break;
  default:
    /* We don't have any other property... */
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
    break;
  }
}

static void viewer_file_get_property(
  const GObject *const object,
  const guint property_id,
  GValue *const value,
  GParamSpec *const pspec
){
  ViewerFile *self = VIEWER_FILE (object);
  switch ((ViewerFileProperty)property_id){
  case PROP_FILENAME:
    g_value_set_string(value, self->filename);
    break;
  case PROP_ZOOM_LEVEL:
    g_value_set_uint(value, self->zoom_level);
    break;
  default:
    /* We don't have any other property... */
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    break;
  }
}

static void viewer_file_class_init(ViewerFileClass *klass){

  GObjectClass *object_class=G_OBJECT_CLASS(klass);

  object_class->dispose=viewer_file_dispose;
  object_class->finalize=viewer_file_finalize;

  object_class->set_property=viewer_file_set_property;
  object_class->get_property=viewer_file_get_property;

  obj_properties[PROP_FILENAME]=g_param_spec_string(
    "filename","Filename","Name of the file to load and display from.",
    NULL  /* default value */,
    G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE
  );

  obj_properties[PROP_ZOOM_LEVEL]=g_param_spec_uint(
    "zoom-level","Zoom level","Zoom level to view the file at.",
    0  /* minimum value */,
    10 /* maximum value */,
    2  /* default value */,
    G_PARAM_READWRITE
  );

  g_object_class_install_properties(
    object_class,
    N_PROPERTIES,
    obj_properties
  );

}

static void viewer_file_init(ViewerFile *const self){
  ViewerFilePrivate *priv=viewer_file_get_instance_private(self);
  /* initialize all public and private members to reasonable default values.
   * They are all automatically initialized to 0 to begin with. */
  priv->input_stream=g_object_new(VIEWER_TYPE_INPUT_STREAM,NULL);
  priv->filename = NULL /* would be set as a property */;
}

void viewer_file_open(ViewerFile *const self,GError *const *const error)
{
  g_return_if_fail(VIEWER_IS_FILE(self));
  g_return_if_fail(!error||!(*error));
  /* do stuff here. */
}
