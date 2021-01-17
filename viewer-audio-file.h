#ifndef __VIEWER_AUDIO_FILE__
#define __VIEWER_AUDIO_FILE__

#include "./viewer-file.h"

G_BEGIN_DECLS

#define VIEWER_TYPE_AUDIO_FILE viewer_audio_file_get_type()
G_DECLARE_FINAL_TYPE(
  ViewerAudioFile, // Name
  viewer_audio_file,
  VIEWER, // Module
  AUDIO_FILE, // Bare name of the type
  ViewerFile // Parent name
)

// No class structure for final type

G_END_DECLS

#endif
