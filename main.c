#include <gio/gio.h>
#include <gio/gunixinputstream.h>
#include <unistd.h> // STDIN/OUT/ERR_FILENO

#include "./viewer-file.h"

ViewerFile *file=NULL;

void getp() {
  GValue s=G_VALUE_INIT;
  GValue u=G_VALUE_INIT;
  g_value_init(&s,G_TYPE_STRING);
  g_value_init(&u,G_TYPE_UINT);
  g_object_get_property(G_OBJECT(file),"filename",&s);
  g_object_get_property(G_OBJECT(file),"zoom-level",&u);
  g_print("filename=%s\n",g_value_get_string(&s));
  g_print("zoom-level=%u\n",g_value_get_uint(&u));
  g_value_unset(&s);
  g_value_unset(&u);
}

void gets() {
  gchar *s=NULL;
  guint u=0;
  g_object_get(G_OBJECT(file),
    "filename",&s,
    "zoom-level",&u,
  NULL);
  g_print("filename=%s\n",s);
  g_print("zoom-level=%u\n",u);
  g_free(s);
  s=NULL;
}

void getv() {
  GValue arr[2]={};
  g_value_init(&(arr[0]),G_TYPE_STRING);
  g_value_init(&(arr[1]),G_TYPE_UINT);
  g_object_getv(G_OBJECT(file),
    (guint)2,
    (const char *[2]){"filename","zoom-level"}, // https://cdecl.org/?q=cast+a+into+array+2+of+pointer+to+const+char
    arr
  );
  g_print("filename=%s\n",g_value_get_string(&(arr[0])));
  g_print("zoom-level=%u\n",g_value_get_uint(&(arr[1])));
  g_value_unset(&(arr[0]));
  g_value_unset(&(arr[1]));
}

int main(){

  // typedef int A,*B;

  // r();

  g_print("\n");
  // g_print("pid: %d\n",getpid());
  g_print("Default\n");
  file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_return_val_if_fail(
    file &&
    G_TYPE_FROM_INSTANCE(file)==VIEWER_TYPE_FILE &&
    G_TYPE_FROM_INSTANCE(file)==viewer_file_get_type()
  ,-1);
  g_print("\n");

  g_object_set(G_OBJECT(file),
    "zoom-level",(guint)6, 
    "filename","/dev/null", 
  NULL);
  g_print("\n");

  getp();g_print("\n");
  gets();g_print("\n");
  getv();g_print("\n");

  // g_object_setv (GObject *object,
  //                guint n_properties,
  //                const gchar *names[],
  //                const GValue values[]);

  /*GValue schar=G_VALUE_INIT;
  g_value_init(&schar,G_TYPE_CHAR);
  g_value_set_schar(&schar,3);
  g_object_set_property(G_OBJECT(file),"zoom-level",&schar);
  g_value_unset(&schar);
  SHOW_ZOOM_LEVEL();
  g_print("\n");*/

  /*GValue ui=G_VALUE_INIT;
  g_value_init(&ui,G_TYPE_UINT);

  g_value_set_uint(&ui,7);
  g_object_set_property(G_OBJECT(file),"zoom-level",&ui);
  SHOW_ZOOM_LEVEL();

  g_value_set_uint(&ui,11);
  g_object_set_property(G_OBJECT(file),"zoom-level",&ui);
  SHOW_ZOOM_LEVEL();

  g_object_set_property(G_OBJECT(file),"non-exist-property",&ui);

  g_value_unset(&ui);*/

  g_object_unref(file);
  file=NULL;
  g_print("\n");
  return 0;

}

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
