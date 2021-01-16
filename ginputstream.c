#include <gio/gunixinputstream.h>

void ginputstream(){

  // Including newline, excluding null termination
  const gssize sz=1024;

  GInputStream *stream=g_unix_input_stream_new(STDIN_FILENO,FALSE);
  g_assert(!g_input_stream_is_closed(stream));

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
  g_assert( !error && 1<=n && n<=sz );
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
  g_assert_no_error(error); 
  stream=NULL;

}
