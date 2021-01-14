#include <gio/gio.h>
#include <gio/gunixinputstream.h>
#include "./viewer-file.h"

#include <unistd.h> // STDIN/OUT/ERR_FILENO

/*void r(){

  // Including newline, excluding null termination
  const gssize sz=1024;

  GInputStream *stream=g_unix_input_stream_new(STDIN_FILENO,FALSE);
  g_return_if_fail(!g_input_stream_is_closed(stream));

  guint8 *buffer=g_malloc0((gsize)sz+1);
  GError *error=NULL;
  // n includs newline
  const gssize n=g_input_stream_read(
    stream,
    buffer,
    sz,
    NULL,
    &error
  );
  g_return_if_fail( !error && 1<=n && n<=sz );
  buffer[n]='\0'; // Keep newline
  // buffer[n-1]='\0'; // Kill newline

  // g_print("%d %d\n",buffer[0],buffer[1]);
  // g_print("%c %c\n",buffer[0],buffer[1]);
  g_print("%s",buffer);

  g_free(buffer);
  buffer=NULL;

  error=NULL;
  g_input_stream_close(
    stream,
    NULL,
    &error
  );
  g_return_if_fail(!error);
  stream=NULL;

}*/

int main(){

  // typedef int A,*B;

  // r();

  g_print("\n");
  g_print("%d\n",getpid());
  ViewerFile *file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_return_val_if_fail(
    file &&
    G_TYPE_FROM_INSTANCE(file)==VIEWER_TYPE_FILE &&
    G_TYPE_FROM_INSTANCE(file)==viewer_file_get_type()
  ,-1);

  GValue val=G_VALUE_INIT;

  g_value_init(&val,G_TYPE_CHAR);
  g_value_set_schar(&val,3);g_object_set_property(G_OBJECT(file),"zoom-level",&val);
  g_value_set_schar(&val,7);g_object_set_property(G_OBJECT(file),"zoom-level",&val);

  // g_value_init(&val,G_TYPE_UINT);
  // g_value_set_uint(&val,11)
  // g_object_set_property(G_OBJECT(file),"zoom-level",&val);

  // g_object_set_property(G_OBJECT(file),"non-exist-property",&val);

  g_value_unset(&val);

  g_object_unref(file);
  // g_object_unref(file);
  file=NULL;
  g_print("\n");
  return 0;

}