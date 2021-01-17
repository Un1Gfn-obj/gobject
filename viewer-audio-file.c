// Override public pure virtfunc w/ private nonvirtfunc

#include "./viewer-audio-file.h"

// Instance structure for final type only
typedef struct _ViewerAudioFile {
  ViewerFile parent_instance;
  // No padding for final type
} ViewerAudioFile;

// Type implementation
G_DEFINE_TYPE(
  ViewerAudioFile,
  viewer_audio_file,
  VIEWER_TYPE_FILE
)

// Destruction

// static void viewer_audio_file_dispose(GObject *const gobject){
//   // Chain up
//   VIEWER_FILE_CLASS(viewer_audio_file_parent_class)->dispose(gobject);
// }

// static void viewer_file_finalize(GObject *const gobject){
//   // Chain up
//   VIEWER_FILE_CLASS(viewer_audio_file_parent_class)->finalize(gobject);
// }

// Construction & methods

static void viewer_audio_file_init(ViewerAudioFile *const self){
  // Initialize
  g_print("viewer_audio_file_init()\n");
}

static ViewerFile *viewer_audio_file_override_open(ViewerFile *const self,const GError *const *const error){
  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );
  g_print("viewer_audio_file_override_open()\n");
  return self;
}

static ViewerFile *viewer_audio_file_chain_close(ViewerFile *const self,const GError *const *const error){
  g_assert( self && VIEWER_IS_FILE(self) && !(error&&(*error)) );
  g_print("before chain\n");
  (VIEWER_FILE_CLASS(viewer_audio_file_parent_class))->close(self,error);
  g_print("after chain\n");
  return self;
}

static void viewer_audio_file_class_init(ViewerAudioFileClass *const klass){
  (VIEWER_FILE_CLASS(klass))->open=viewer_audio_file_override_open;
  (VIEWER_FILE_CLASS(klass))->close=viewer_audio_file_chain_close;
}
