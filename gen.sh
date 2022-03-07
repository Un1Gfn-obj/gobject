#!/bin/bash

# https://stackoverflow.com/questions/15184358/how-to-avoid-bash-command-substitution-to-remove-the-newline-character

#   H0="$H"; cat <<__EOF | sed 's/^  //g' | IFS= read -rd '' H; H="$H0$H"
# __EOF

#     H0="$H"; cat <<____EOF | sed 's/^    //g' | IFS= read -rd '' H; H="$H0$H"
# ____EOF

# https://stackoverflow.com/questions/15184358/how-to-avoid-bash-command-substitution-to-remove-the-newline-character
shopt -s lastpipe

# namespace, type, type instance, class (base type)
BN=""; BT=""; BTI=""; BC="";

# namespace, type, type instance, class
N=""; T=""; TI=""; C="";

# true if final, false if derivable
F=true

# methods
pubM=(); privM=(); virtpubM=(); virtprivM=();

function help2 {
  1>&2 echo "$(basename "$0") <namespace>::<type> [-f] [-b <basetype>] [--pub|priv <method>] ..."
  1>&2 echo "$(basename "$0") <namespace>::<type>  -d  [-b <basetype>] [--pub|priv|virtpub|virtpriv <method>] ..."
  1>&2 echo "$(basename "$0") -h|--help"
  1>&2 echo "$(basename "$0") --demo"
  exit 1
}

function demo {
  CMD=("$0" -f ns::dict --pub cksum)
  # "${CMD[@]}" | less -SRM +%
  CMD+=(-b ns::kvp)
  "${CMD[@]}" | less -SRM +%
  # read -r
  # clear
  # tput reset
  CMD=( "$0" -d ns::dict --pub cksum
    --virtpub close
    --virtpub open
    --virtpub validate
    --virtpub compress
    --virtpub encrypt
  )
  # "${CMD[@]}" | less -SRM +%
  CMD+=(-b ns::kvp)
  "${CMD[@]}" | less -SRM +%
}

function nt2nt {
  [[ "$1" =~ ^(([0-9A-Za-z]+)::([0-9A-Za-z]+))$ ]] || help2
  [ -n "${BASH_REMATCH[2]}" ] || help2
  [ -n "${BASH_REMATCH[3]}" ] || help2
  printf -v "$2" '%s' "${BASH_REMATCH[2],,}"
  printf -v "$3" '%s' "${BASH_REMATCH[3],,}"
  printf -v "$4" '%s' "${!2^}${!3^}"
  printf -v "$5" '%s' "${!2^}${!3^}Class"
}

function show {
  if "$F"; then echo "final"; else echo "derivable"; fi
  echo
  echo "pub      - ${pubM[*]/%/()}"
  echo "priv     - ${privM[*]/%/()}"
  echo "virtpub  - ${virtpubM[*]/%/()}"
  echo "virtpriv - ${virtprivM[*]/%/()}"
  echo
}

function H_variant_0 {
  if "$F"; then
    echo "G_DECLARE_FINAL_TYPE(${TI}, ${N,,}_${T,,}, ${N^^}, ${T^^}, ${BTI})"$'\n'
  else
    cat <<____EOF | sed 's/^    //g'
    G_DECLARE_DERIVABLE_TYPE(${TI}, ${N,,}_${T,,}, ${N^^}, ${T^^}, ${BTI})

    // type instance structure of a derivable class should be defined in its H/header file
    typedef struct {
      ${BC} parent_class;
      // class virtual functions
____EOF
    for f in "${virtpubM[@]}"; do
      echo "  void (*${f})(${TI} *${T,,}, GError **error);"
    done
    cat <<____EOF | sed 's/^    //g'
      // padding to allow adding up to 12 new virtual functions without breaking ABI
      gpointer padding[12];
    } ${C};
____EOF
    echo
  fi
}

function H_emit {

  cat <<__EOF | sed 's/^  //g'
  // ${N,,}_${T,,}.h

  // $(basename "$0") ${ARGSBAK[*]}

  // #pragma once
  #ifndef ${N^^}_${T^^}_H
  #define ${N^^}_${T^^}_H

  #include <glib-object.h>

  G_BEGIN_DECLS

  #define ${N^^}_TYPE_${T^^} ${N,,}_${T,,}_get_type()
__EOF
  
  H_variant_0

  cat <<__EOF | sed 's/^  //g'
  ${TI} *${N,,}_${T,,}_new();

  G_END_DECLS

  #endif
__EOF

}

function C_emit {

  cat <<__EOF | sed 's/^  //g'
  // ${N,,}_${T,,}.c

  // $(basename "$0") ${ARGSBAK[*]}

  #include "${N,,}_${T,,}.h"
__EOF
  echo

  if "$F"; then
    cat <<____EOF | sed 's/^    //g'
    // type instance structure of a final class should be defined in its C/source file
    typedef struct {
      ${BTI} parent_instance;
      // private data of a final class should be placed in the instance structure
      void *${T,,};
      gchar *string;
      guint num;
      GInputStream *stream;
    } ${TI};

    G_DEFINE_TYPE(${TI}, ${N,,}_${T,,}, ${BN^^}_TYPE_${BT^^})
____EOF
  else
    cat <<____EOF | sed 's/^    //g'
    // (A) derivable without private
    // G_DEFINE_TYPE(${TI}, ${N,,}_${T,,}, ${BN^^}_TYPE_${BT^^})

    // (B) derivable with private
    // private data for a derivable class must be included in a private structure, and G_DEFINE_TYPE_WITH_PRIVATE must be used
    typedef struct {
      void *${T,,};
      gchar *string;
      guint num;
      GInputStream *stream;
    } ${TI}Private;
    //
    G_DEFINE_TYPE_WITH_PRIVATE(${TI}, ${N,,}_${T,,}, ${BN^^}_TYPE_${BT^^})
____EOF
  fi
  echo

  echo "static void ${N,,}_${T,,}_dispose(${BTI} *${BTI,,}){"
  if "$F"; then
    echo "  g_clear_object(${N^^}_${T^^}(${BTI,,})->input_stream);"
  else
    echo "  ${TI}Private *priv = ${N,,}_${T,,}_get_instance_private(${N^^}_${T^^}(${BTI,,}));"
    echo "  g_clear_object(&priv->input_stream);"
  fi
  echo "  ${BN^^}_${BT^^}_CLASS(${N,,}_${T,,}_parent_class)->dispose(${BTI,,});"
  echo "}"
  echo

  echo "static void ${N,,}_${T,,}_finalize(${BTI} *${BTI,,}){"
  if "$F"; then
    echo "  g_free(${N^^}_${T^^}(${BTI,,})->filename);"
  else
    echo "  ${TI}Private *priv = ${N,,}_${T,,}_get_instance_private(${N^^}_${T^^}(${BTI,,}));"
    echo "  g_free(priv->filename);"
  fi
  echo "  ${BN^^}_${BT^^}_CLASS(${N,,}_${T,,}_parent_class)->finalize(${BTI,,});"
  echo "}"
  echo

  cat <<__EOF | sed 's/^  //g'
  // forward declarations
  // ...

  enum {
    RESERVED = 0,
    PROP_STR,
    PROP_UINT,
    N_PROPERTIES
  };

  static GParamSpec *obj_properties[N_PROPERTIES] = {};

  static void ${N,,}_${T,,}_class_init(${C} *klass){

    ${BC} *${BT,,}_class = ${BN^^}_${BT^^}_CLASS(klass);
    ${BT,,}_class->dispose = {BN,,}_${BT,,}_dispose;
    ${BT,,}_class->finalize = {BN,,}_${BT,,}_finalize;

    ${BT,,}_class->set_property = ${N,,}_${T,,}_set_property;
    ${BT,,}_class->get_property = ${N,,}_${T,,}_get_property;
    obj_properties[PROP_STR] = g_param_spec_string(
      "string",
      "String",
      "A string parameter",
      NULL  /* default */,
      G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE
    );
    obj_properties[PROP_UINT] = g_param_spec_uint(
      "unsigned-integer",
      "Unsigned integer",
      "A unsigned integer parameter",
      0   /* min */,
      100 /* max */,
      75  /* default */,
      G_PARAM_READWRITE
    );
    g_object_class_install_properties(${BT,,}_class, N_PROPERTIES, obj_properties);

  }
__EOF
  echo

  echo "static void ${N,,}_${T,,}_init(${TI} *self){"
  if "$F"; then
    cat <<____EOF | sed 's/^    //g'
      // initialize private members (final type cannot have public member)
      self->${T,,} = NULL;
      self->input_stream = g_object_new(${N^^}_TYPE_INPUT_STREAM, NULL);
      self->filename = NULL;
____EOF
  else
    cat <<____EOF | sed 's/^    //g'
      // initialize public members
      // ...
      // initialize private members
      ${TI}Private *priv = ${N,,}_${T,,}_get_instance_private(self);
      priv->${T,,} = NULL;
      priv->input_stream = g_object_new(${N^^}_TYPE_INPUT_STREAM, NULL);
      priv->filename = NULL;
____EOF
  fi
  echo "}"

}

{

  (($#>=1)) || help2

  ARGSBAK=("$@")
  TEMP=$(/bin/getopt -n 'gen.sh' -o 'hfdb:' -l 'help,demo,pub:,virtpub:,virtpriv:,priv:' -- "$@") || help2
  eval set -- "$TEMP"
  unset -v TEMP

  nt2nt "g::object" BN BT BTI BC

  while true; do
    case x"$1" in
      x"-h"|x"--help") help2; exit;;
      x"--demo")       demo; exit;;
      x"-b") shift; nt2nt "$1" BN BT BTI BC; shift;;
      x"-d") F=false; shift;;
      x"-f") F=true; shift;;
      x"--pub"|x"--priv"|x"--virtpub"|x"--virtpriv") declare -n A="${1:2}M"; shift; A+=("$1"); shift;;
      x"--") shift; ((1==$#)) || { echo "err: there should be exactly one positional parameter"; exit 1; }; break;;
      *) echo "err: invalid parameter '$1'"; exit 1;;
    esac
  done

  if "$F"; then
    ((0==${#virtpubM[@]}))  || { echo "err: virtual method not allowed in final (non-derivable) type"; exit 1; }
    ((0==${#virtprivM[@]})) || { echo "err: virtual method not allowed in final (non-derivable) type"; exit 1; }
  fi

  nt2nt "$1" N T TI C

  # pygmentize -l c <<<"$H"

  echo "/$(printf -- '*%.0s' {1..78})/"
  echo
  H_emit
  echo

  echo "/$(printf -- '*%.0s' {1..78})/"
  echo
  C_emit
  echo

}; exit
