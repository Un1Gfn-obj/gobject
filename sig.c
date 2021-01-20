#include <gio/gio.h> // GNotification
#include <glib.h> // g_alloca() g_usleep
#include "./viewer-file.h"

static void changed_event(){

  gchar *const id=g_alloca(sizeof(gchar));
  *id=0;

  // gchar id2=0;

  GApplication *application =g_application_new("com.github.Un1Gfn.gobject",G_APPLICATION_FLAGS_NONE);
  g_application_register(application,NULL,NULL);
  GNotification *notification=g_notification_new("Viewer::File::write()");

  g_application_send_notification(application,id,notification);
  g_usleep(3000000UL);
  g_application_withdraw_notification(application,id);

  g_object_unref(notification);
  g_object_unref(application);

}

void sig(){

  ViewerFile *const file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_assert_nonnull(file);

  g_signal_connect(file,"changed",(GCallback)changed_event,NULL);

  const gchar *buffer="Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
  viewer_file_write(file,(const guint8*)buffer,strlen(buffer));

}
