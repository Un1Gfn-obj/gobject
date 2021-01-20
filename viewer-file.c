// Cannot split into viewer-file{,-editable{,-lossy}}.{c,h} since they may depend on ViewerFilePrivate and/or G_DEFINE_TYPE_WITH_CODE()

#include <gio/gio.h> // GInputStream
#include "./viewer-file.h"
#include "./viewer-editable.h"
#include "./viewer-editable-lossy.h"

// Private structure
typedef struct {
  // set/gettable properties
  gchar *filename;
  guint zoom_level;
  gdouble autosave_frequency; // Interface
  // Non-set/gettable properties
  GInputStream *input_stream;
} ViewerFilePrivate;

// No instance structure for derivable type

// These two are implemented below
static void viewer_file_editable_interface_init(ViewerEditableInterface *const);
static void viewer_file_editable_lossy_interface_init(ViewerEditableLossyInterface *const);

G_DEFINE_TYPE_WITH_CODE(
  ViewerFile,
  viewer_file,
  G_TYPE_OBJECT,
  G_ADD_PRIVATE(
    ViewerFile
  )
  // https://developer.gnome.org/gobject/2.66/howto-interface-prerequisite.html
  // The order of adding interface implementations to the main object 
  // ... must be invoked first on the interfaces which have no prerequisites and then on the others.
  G_IMPLEMENT_INTERFACE(
    VIEWER_TYPE_EDITABLE,
    viewer_file_editable_interface_init
  )
  G_IMPLEMENT_INTERFACE(
    VIEWER_TYPE_EDITABLE_LOSSY,
    viewer_file_editable_lossy_interface_init
  )
)/*
https://developer.gnome.org/gobject/stable/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
G_DEFINE_TYPE() does the following:
  static void viewer_file_class_init(ViewerFileClass*);
  static void viewer_file_init(ViewerFile*);
  static gpointer viewer_file_parent_class=NULL;
  GType viewer_file_get_type(){...}
*/

// Destruction

static void viewer_file_dispose(GObject *const gobject){
  /* In dispose(), you are supposed to free all types referenced from this
   * object which might themselves hold a reference to self. Generally,
   * the most simple solution is to unref all members on which you own a 
   * reference.
   */
  /* dispose() might be called multiple times, so we must guard against
   * calling g_object_unref() on an invalid GObject by setting the member
   * NULL; g_clear_object() does this for us.
   */
  g_clear_object(
    &(
      (
        (ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(gobject))
      )->input_stream
    )
  );
  /* Always chain up to the parent class; there is no need to check if
   * the parent class implements the dispose() virtual function: it is
   * always guaranteed to do so
   */
  g_print("Viewer::File::dispose() ");
  g_print("chain ");
  g_print("GObjectClass::dispose()\n");
  G_OBJECT_CLASS(viewer_file_parent_class)->dispose(gobject);
}

static void viewer_file_finalize(GObject *const gobject){
  g_free((
    (ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(gobject))
  )->filename);
  g_print("Viewer::File::finalize() ");
  g_print("chain ");
  g_print("GObjectClass::finalize()\n");
  G_OBJECT_CLASS(viewer_file_parent_class)->finalize(gobject);
}

// Properties

typedef enum {

  PROP_FILENAME=1,
  PROP_ZOOM_LEVEL,
  N_PROPERTIES,

  PROP_AUTOSAVE_FREQUENCY

} ViewerFileProperty;

static GParamSpec *obj_properties[N_PROPERTIES]={};

static void viewer_file_set_property(
  GObject *const object,
  const guint property_id,
  const GValue *const value,
  GParamSpec *const pspec
){
  ViewerFilePrivate *const priv=viewer_file_get_instance_private(VIEWER_FILE(object));
  switch((ViewerFileProperty)property_id){
  case PROP_FILENAME:
    g_free(priv->filename);
    priv->filename=g_value_dup_string(value);
    // A:; // Label
    // g_print((priv->filename)?"setting filename to %s\n":"setting filename to %p\n",priv->filename);
    g_print("setting filename to %s\n",priv->filename);
    break;
  case PROP_ZOOM_LEVEL:
    priv->zoom_level=g_value_get_uint(value);
    g_print("setting zoom level to %u\n", priv->zoom_level);
    break;
  case PROP_AUTOSAVE_FREQUENCY:
    priv->autosave_frequency=g_value_get_double(value);
    g_print("setting autosave frequency to %lf\n", priv->autosave_frequency);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object,property_id,pspec);
    break;
  }
}

static void viewer_file_get_property(
  GObject *const object,
  const guint property_id,
  GValue *const value,
  GParamSpec *const pspec
){
  ViewerFilePrivate *const priv=viewer_file_get_instance_private(VIEWER_FILE(object));
  switch ((ViewerFileProperty)property_id){
  case PROP_FILENAME:
    g_value_set_string(value, priv->filename);
    break;
  case PROP_ZOOM_LEVEL:
    g_value_set_uint(value, priv->zoom_level);
    break;
  case PROP_AUTOSAVE_FREQUENCY:
    g_value_set_double(value,priv->autosave_frequency);
    break;
  default:
    /* We don't have any other property... */
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, property_id, pspec);
    break;
  }
}

// Construction & methods

// Mere virtfunc real implementation
static ViewerFile *viewer_file_real_close(ViewerFile *const self,const GError *const *const error){
  // Default implementation for the virtual method.
  g_print("Viewer::File::close()\n");
  return self;
}

static void viewer_file_class_init(ViewerFileClass *const klass){

  g_print("Viewer::FileClass::init()\n");

  GObjectClass *object_class=G_OBJECT_CLASS(klass);

  // Destruction
  object_class->dispose=viewer_file_dispose;
  object_class->finalize=viewer_file_finalize;
  klass->dispose=viewer_file_dispose;
  klass->finalize=viewer_file_finalize;

  // Properties
  object_class->set_property=viewer_file_set_property;
  object_class->get_property=viewer_file_get_property;
  obj_properties[PROP_FILENAME]=g_param_spec_string(
    "filename","Filename","Name of the file to load and display from.",
    "/dev/null"  /* default value */,
    G_PARAM_CONSTRUCT | G_PARAM_READWRITE // https://developer.gnome.org/gobject/stable/gobject-GParamSpec.html#GParamFlags
  );
  obj_properties[PROP_ZOOM_LEVEL]=g_param_spec_uint(
    "zoom-level","Zoom level","Zoom level to view the file at.",
    0  /* minimum value */,
    10 /* maximum value */,
    2  /* default value */,
    G_PARAM_CONSTRUCT | G_PARAM_READWRITE // https://developer.gnome.org/gobject/stable/gobject-GParamSpec.html#GParamFlags
  );
  g_object_class_install_properties(object_class,N_PROPERTIES,obj_properties);
  g_object_class_override_property(object_class,PROP_AUTOSAVE_FREQUENCY,"autosave-frequency");

  // Segfault
  // g_free(obj_properties[PROP_FILENAME]);
  // g_free(obj_properties[PROP_ZOOM_LEVEL]);

  // Pure virtfunc (mandates implementation in children)
  klass->open=NULL;

  // Mere virtfunc
  klass->close=viewer_file_real_close;

}

static void viewer_file_init(ViewerFile *const self){

  g_print("Viewer::File::init()\n");

  //                                                                   //   compile-time runtime (O)K (W)arning (E)rror
  // #define VIEWER_TYPE_INPUT_STREAM g_input_stream_get_type()        //          O        E
  // #define VIEWER_TYPE_INPUT_STREAM g_filter_input_stream_get_type() //          O        E
  // #define VIEWER_TYPE_INPUT_STREAM g_file_input_stream_get_type()   //          O        O
  // #define VIEWER_TYPE_INPUT_STREAM g_memory_input_stream_get_type() //          O        O
  // #define VIEWER_TYPE_INPUT_STREAM g_unix_input_stream_get_type()   //          W        E

  // #define VIEWER_TYPE_INPUT_STREAM G_TYPE_INPUT_STREAM
  #define VIEWER_TYPE_INPUT_STREAM G_TYPE_FILE_INPUT_STREAM
  (
    (ViewerFilePrivate*)viewer_file_get_instance_private(self)
  )->input_stream=g_object_new(VIEWER_TYPE_INPUT_STREAM,NULL);

}

// Pure virtfunc redirect implementation
ViewerFile *viewer_file_open(ViewerFile *const self,const GError *const *const error){

  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );

  ViewerFileClass *const klass=VIEWER_FILE_GET_CLASS(self);

  if(klass->open==NULL)
    g_error("pure virtual Viewer::File::open() not overriden\n");

  klass->open(self,error);
  return self;

}

// Mere virtfunc redirect implementation
ViewerFile *viewer_file_close(ViewerFile *const self,const GError *const *const error){

  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );

  ViewerFileClass *const klass=VIEWER_FILE_GET_CLASS(self);
  /* if the method is purely virtual, then it is a good idea to
   * check that it has been overridden before calling it, and,
   * depending on the intent of the class, either ignore it silently
   * or warn the user.
   */
  g_assert( klass->close!=NULL );
  klass->close(self,error);

  return self;

}

// Viewer::File::Editable

static void viewer_file_editable_save(ViewerEditable *const editable,GError *const *const error){
  g_print(
    "Viewer::File::Editable::save() %s.\n",
    ((ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(editable)))->filename
  );
}

static void viewer_file_editable_undo(ViewerEditable *const editable,const guint n_steps){
  g_print(
    "Viewer::File::Editable::undo() %s.\n",
    ((ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(editable)))->filename
  );
}

static void viewer_file_editable_redo(ViewerEditable *const editable,const guint n_steps){
  g_print(
    "Viewer::File::Editable::redo() %s.\n",
    ((ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(editable)))->filename
  );
}

static void viewer_file_editable_interface_init(ViewerEditableInterface *iface){
  g_print("Viewer::File::Editable::init()\n");
  // #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  iface->save=viewer_file_editable_save;
  iface->undo=viewer_file_editable_undo;
  iface->redo=viewer_file_editable_redo;
  // #pragma GCC diagnostic pop
}

// Viewer::File::EditableLossy

static void viewer_file_editable_lossy_compress(ViewerEditableLossy *const editable){
  g_print (
    "Viewer::File::EditableLossy::compress() %s.\n",
    ((ViewerFilePrivate*)viewer_file_get_instance_private(VIEWER_FILE(editable)))->filename
  );
}

static void viewer_file_editable_lossy_interface_init(ViewerEditableLossyInterface *const iface){
   g_print("Viewer::File::EditableLossy::init()\n");
   // #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
   iface->compress=viewer_file_editable_lossy_compress;
   // #pragma GCC diagnostic pop
}
