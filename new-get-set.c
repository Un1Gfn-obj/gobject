#include "./viewer-file.h"

static ViewerFile *file=NULL;

static void get1B1() {
  GValue s=G_VALUE_INIT,u=G_VALUE_INIT;
  g_object_get_property(G_OBJECT(file),"filename",g_value_init(&s,G_TYPE_STRING));
  g_object_get_property(G_OBJECT(file),"zoom-level",g_value_init(&u,G_TYPE_UINT));
  g_print("filename=%s\n",g_value_get_string(&s));
  g_print("zoom-level=%u\n",g_value_get_uint(&u));
  g_value_unset(&s);
  g_value_unset(&u);
}

static void getALL() {
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

static void getARR() {
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

static void set1B1(const gchar *const s,const guint u){
  GValue s2=G_VALUE_INIT;
  GValue u2=G_VALUE_INIT;
  g_value_set_static_string(g_value_init(&s2,G_TYPE_STRING),s);
  g_value_set_uint(g_value_init(&u2,G_TYPE_UINT),u);
  g_object_set_property(G_OBJECT(file),"filename",&s2);
  g_object_set_property(G_OBJECT(file),"zoom-level",&u2);
  g_value_unset(&s2);
  g_value_unset(&u2);
}

static void setALL(const gchar *const s,const guint u){
  g_object_set(G_OBJECT(file),
    "filename",s,
    "zoom-level",u,
  NULL);
}

static void setARR(const gchar *const s,const guint u){
  GValue arr[2]={};
  g_value_set_static_string(g_value_init(&(arr[0]),G_TYPE_STRING),s);
  g_value_set_uint(g_value_init(&(arr[1]),G_TYPE_UINT),u);
  g_object_setv(G_OBJECT(file),
    (guint)2,
    (const gchar *[2]){"filename","zoom-level"}, // https://cdecl.org/?q=cast+a+into+array+2+of+pointer+to+const+char
    arr
  );
}

static void newALL(const gchar *const s,const guint u){
  g_return_if_fail(file==NULL);
  file=(ViewerFile*)g_object_new(VIEWER_TYPE_FILE,
    "filename",s, 
    "zoom-level",u, 
  NULL);
}

static void newARR(const gchar *const s,const guint u){
  g_return_if_fail(file==NULL);
  GValue arr[2]={};
  g_value_set_static_string(g_value_init(&(arr[0]),G_TYPE_STRING),s);
  g_value_set_uint(g_value_init(&(arr[1]),G_TYPE_UINT),u);
  file=(ViewerFile*)g_object_new_with_properties(VIEWER_TYPE_FILE,
    (guint)2,
    (const gchar *[2]){"filename","zoom-level"}, // https://cdecl.org/?q=cast+a+into+array+2+of+pointer+to+const+char
    arr
  );
}

void new_get_set(){

  g_print("customized new:\n");
  newALL("/tmp/newALL",7);
  getALL();g_object_unref(file);file=NULL;
  newARR("/tmp/newARR",9);
  getARR();g_object_unref(file);file=NULL;
  g_print("\n");

  g_print("default new:\n");
  file=g_object_new(VIEWER_TYPE_FILE,NULL);
  g_return_if_fail(
    file &&
    G_IS_OBJECT(file) &&
    0==g_strcmp0("ViewerFile",G_OBJECT_TYPE_NAME(file)) &&
    0==g_strcmp0("ViewerFile",G_OBJECT_CLASS_NAME(G_OBJECT_GET_CLASS(file))) &&
    G_OBJECT_TYPE(file)==VIEWER_TYPE_FILE &&
    G_OBJECT_TYPE(file)==viewer_file_get_type()
  );
  getALL();
  g_print("\n");

  set1B1("/dev/stdin",0);
  get1B1();g_print("\n");
  setALL("/dev/stdout",1);
  getALL();g_print("\n");
  setARR("/dev/stderr",2);
  getARR();g_print("\n");

  g_print("g_value_transform:\n");
  GValue schar=G_VALUE_INIT;
  g_value_set_schar(g_value_init(&schar,G_TYPE_CHAR),3);
  g_object_set_property(G_OBJECT(file),"zoom-level",&schar);
  g_value_unset(&schar);
  getALL();
  g_print("\n");

  GValue ui=G_VALUE_INIT;
  g_value_init(&ui,G_TYPE_UINT);
  g_print("out of range:\n");
  g_value_set_uint(&ui,11);
  g_object_set_property(G_OBJECT(file),"zoom-level",&ui);
  getALL();
  g_print("\n");

  g_print("non-exist property:\n");
  g_object_set_property(G_OBJECT(file),"cheeki-breeki",&ui);
  g_value_unset(&ui);
  g_print("\n");

  g_object_unref(file);
  file=NULL;

}