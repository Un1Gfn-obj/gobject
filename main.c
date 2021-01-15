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
    (const gchar *[2]){"filename","zoom-level"}, // https://cdecl.org/?q=cast+a+into+array+2+of+pointer+to+const+char
    arr
  );
  g_print("filename=%s\n",g_value_get_string(&(arr[0])));
  g_print("zoom-level=%u\n",g_value_get_uint(&(arr[1])));
  g_value_unset(&(arr[0]));
  g_value_unset(&(arr[1]));
}

void setp(const gchar *const s,const guint u){
  GValue s2=G_VALUE_INIT;
  GValue u2=G_VALUE_INIT;
  g_value_init(&s2,G_TYPE_STRING);
  g_value_init(&u2,G_TYPE_UINT);
  // g_value_set_string(&s2,s);
  g_value_set_static_string(&s2,s);
  g_value_set_uint(          &u2,u);
  g_object_set_property(G_OBJECT(file),"filename",&s2);
  g_object_set_property(G_OBJECT(file),"zoom-level",&u2);
  g_value_unset(&s2);
  g_value_unset(&u2);
}

void sets(const gchar *const s,const guint u){
  g_object_set(G_OBJECT(file),
    "filename",s, 
    "zoom-level",u, 
  NULL);
}

void setv(const gchar *const s,const guint u){
  GValue arr[2]={};
  g_value_init(&(arr[0]),G_TYPE_STRING);
  g_value_init(&(arr[1]),G_TYPE_UINT);
  g_value_set_static_string(&(arr[0]),s);
  g_value_set_uint(&(arr[1]),u);
  g_object_setv(G_OBJECT(file),
    (guint)2,
    (const gchar *[2]){"filename","zoom-level"}, // https://cdecl.org/?q=cast+a+into+array+2+of+pointer+to+const+char
    arr
  );
}

// void r();

int main(){

  // r();

  g_print("\n");
  // g_print("pid: %d\n",getpid());
  g_print("default:\n");
  file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_return_val_if_fail(
    file &&
    G_TYPE_FROM_INSTANCE(file)==VIEWER_TYPE_FILE &&
    G_TYPE_FROM_INSTANCE(file)==viewer_file_get_type()
  ,-1);
  g_print("\n");

  setp("/dev/stdin",0);
  getp();g_print("\n");
  sets("/dev/stdout",1);
  gets();g_print("\n");
  setv("/dev/stderr",2);
  getv();g_print("\n");

  g_print("g_value_transform:\n");
  GValue schar=G_VALUE_INIT;
  g_value_init(&schar,G_TYPE_CHAR);
  g_value_set_schar(&schar,3);
  g_object_set_property(G_OBJECT(file),"zoom-level",&schar);
  g_value_unset(&schar);
  gets();
  g_print("\n");

  GValue ui=G_VALUE_INIT;
  g_value_init(&ui,G_TYPE_UINT);

  g_print("out of range:\n");
  g_value_set_uint(&ui,11);
  g_object_set_property(G_OBJECT(file),"zoom-level",&ui);
  gets();
  g_print("\n");

  g_print("non-exist property:\n");
  g_object_set_property(G_OBJECT(file),"cheeki-breeki",&ui);
  g_value_unset(&ui);
  g_print("\n");

  g_object_unref(file);
  file=NULL;
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
