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
)/*
https://developer.gnome.org/gobject/stable/gobject-Type-Information.html#G-DECLARE-FINAL-TYPE:CAPS
G_DECLARE_FINAL_TYPE() does the following:
  GType viewer_audio_file_get_type();
  static inline ViewerAudioFile *VIEWER_AUDIO_FILE(gpointer) // Type cast
  static inline gboolean VIEWER_IS_FILE(gpointer){...}       // Type check
  typedef struct _ViewerAudioFileClass { ViewerFile parent_class; } ViewerAudioFileClass;
  typedef struct _ViewerAudioFile ViewerAudioFile;
*/

// No class structure for final type

G_END_DECLS

#endif
