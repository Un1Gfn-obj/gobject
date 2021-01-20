// Override public pure virtfunc w/ private nonvirtfunc

#include "./viewer-file.h"
#include "./viewer-audio-file.h"
#include "./viewer-editable.h"

// Instance structure for final type only
struct _ViewerAudioFile {
  ViewerFile parent_instance;
  // No padding for final type
};

static void viewer_audio_file_editable_interface_init(ViewerEditableInterface *const);

G_DEFINE_TYPE_WITH_CODE(
  ViewerAudioFile,
  viewer_audio_file,
  VIEWER_TYPE_FILE,
  G_IMPLEMENT_INTERFACE(
    VIEWER_TYPE_EDITABLE,
    viewer_audio_file_editable_interface_init
  )
)/*
https://developer.gnome.org/gobject/stable/gobject-Type-Information.html#G-DEFINE-TYPE:CAPS
G_DEFINE_TYPE() does the following:
  [Please refer to viewer-file.c]
*/

// Destruction

static void viewer_audio_file_dispose(GObject *const gobject){
  g_print("Viewer::AudioFile::dispose() ");
  g_print("chain ");
  VIEWER_FILE_CLASS(viewer_audio_file_parent_class)->dispose(gobject);
}

static void viewer_file_finalize(GObject *const gobject){
  g_print("Viewer::AudioFile::finalize() ");
  g_print("chain ");
  VIEWER_FILE_CLASS(viewer_audio_file_parent_class)->finalize(gobject);
}

// Construction & methods

static void viewer_audio_file_init(ViewerAudioFile *const self){
  // Initialize
  g_print("Viewer::AudioFile::init()\n");
}

static ViewerFile *viewer_audio_file_override_open(ViewerFile *const self,const GError *const *const error){
  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );
  g_print("Viewer::AudioFile::open()\n");
  return self;
}

static ViewerFile *viewer_audio_file_chain_close(ViewerFile *const self,const GError *const *const error){
  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );
  g_print("Viewer::AudioFile::close() ");
  g_print("chain ");
  VIEWER_FILE_CLASS(viewer_audio_file_parent_class)->close(self,error);
  return self;
}

static void viewer_audio_file_class_init(ViewerAudioFileClass *const klass){
  (VIEWER_FILE_CLASS(klass))->open=viewer_audio_file_override_open;
  (VIEWER_FILE_CLASS(klass))->close=viewer_audio_file_chain_close;
  (G_OBJECT_CLASS(klass))->dispose=viewer_audio_file_dispose;
  (G_OBJECT_CLASS(klass))->finalize=viewer_file_finalize;
}

// Viewer::AudioFile::Editable

// To call the base class implementation of an interface method from a derived class where than interface method has been overridden, stash away the pointer returned from g_type_interface_peek_parent() in a global variable
static ViewerEditableInterface *viewer_editable_parent_interface=NULL;

static void viewer_audio_file_editable_save (ViewerEditable *const editable,GError *const *const error){
  // ViewerAudioFile *self=VIEWER_AUDIO_FILE(editable);
  g_print("Viewer::AudioFile::Editable::save() ");
  g_print("chain ");
  g_assert_nonnull(viewer_editable_parent_interface->save);
  viewer_editable_parent_interface->save(editable, error);
}

static void viewer_audio_file_editable_interface_init(ViewerEditableInterface *const iface){
  g_print("Viewer::AudioFile::Editable::init()\n");
  viewer_editable_parent_interface=g_type_interface_peek_parent(iface);
  /* Override the implementation of save(). */
  iface->save=viewer_audio_file_editable_save;

  /*
   * Leave iface->undo and ->redo alone, they are already set to the
   * base class implementation.
   */
}
