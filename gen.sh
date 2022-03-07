#!/bin/bash

# https://stackoverflow.com/questions/15184358/how-to-avoid-bash-command-substitution-to-remove-the-newline-character

#   H0="$H"; cat <<__EOF | sed 's/^  //g' | IFS= read -rd '' H; H="$H0$H"
# __EOF

#     H0="$H"; cat <<____EOF | sed 's/^    //g' | IFS= read -rd '' H; H="$H0$H"
# ____EOF

# https://stackoverflow.com/questions/15184358/how-to-avoid-bash-command-substitution-to-remove-the-newline-character
shopt -s lastpipe

# basetype
B="GObject"

# namespace
N=""

# type
T=""

# type instance
TI=""

# class
C=""

# derivable?
D=false

# public methods
pubM=()

# private methods
privM=()

# virtual public methods
virtpubM=()

# virtual private methods
virtprivM=()

function help2 {
  1>&2 echo "$(basename "$0") <namespace>::<type> [-f] [-b <basetype>] [--pub|priv <method>] ..."
  1>&2 echo "$(basename "$0") <namespace>::<type>  -d  [-b <basetype>] [--pub|priv|virtpub|virtpriv <method>] ..."
  1>&2 echo "$(basename "$0") -h|--help"
  1>&2 echo "$(basename "$0") --demo"
  exit 1
}

function demo {
  "$0" -f nS::dIcT -b NSKeyValuePair --pub cksum
  read -r
  clear
  tput reset
  "$0" -d nS::dIcT -b NSKeyValuePair --pub cksum \
    --virtpub close \
    --virtpub open \
    --virtpub validate \
    --virtpub compress \
    --virtpub encrypt
}

function show {
  if "$D"; then echo "derivable"; else echo "final"; fi
  echo
  echo "pub      - ${pubM[*]/%/()}"
  echo "priv     - ${privM[*]/%/()}"
  echo "virtpub  - ${virtpubM[*]/%/()}"
  echo "virtpriv - ${virtprivM[*]/%/()}"
  echo
}

function H_variant_0 {
  if "$D"; then
    # https://stackoverflow.com/questions/15184358/how-to-avoid-bash-command-substitution-to-remove-the-newline-character
    cat <<____EOF | sed 's/^    //g'
    G_DECLARE_DERIVABLE_TYPE(${TI}, ${N,,}_${T,,}, ${N^^}, ${T^^}, ${B})

    struct _${C} {

      GObjectClass parent_class;

      // class virtual functions
____EOF
    for f in "${virtpubM[@]}"; do
      echo "  void (*${f})(${TI} *${T,,}, GError **error);"
    done
    cat <<____EOF | sed 's/^    //g'

      // padding to allow adding up to 12 new virtual functions without breaking ABI
      gpointer padding[12];

    };
____EOF
  else
    echo "G_DECLARE_FINAL_TYPE(${TI}, ${N,,}_${T,,}, ${N^^}, ${T^^}, ${B})"$'\n'
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

  // private structure definition
  typedef struct {

    char *${T,,};

    // other private fields
    // ...

  } ${TI}Private;

  // forward declarations
  // ...

__EOF

}

{

  (($#>=1)) || help2

  ARGSBAK=("$@")
  TEMP=$(/bin/getopt -n 'gen.sh' -o 'hfdb:' -l 'help,demo,pub:,virtpub:,virtpriv:,priv:' -- "$@") || help2
  eval set -- "$TEMP"
  unset -v TEMP

  while true; do
    case x"$1" in
      x"-h"|x"--help") help2; exit;;
      x"--demo")       demo; exit;;
      #
      x"-b") shift; B="$1"; shift;;
      #
      # x"-d") echo "err: derivable type not implemented yet"; exit 1;; # D=true;  shift;;
      x"-d") D=true; shift;;
      x"-f") D=false; shift;;
      #
      x"--pub")      shift; pubM+=("$1");      shift;;
      x"--virtpub")  shift; virtpubM+=("$1");  shift;;
      x"--virtpriv") shift; virtprivM+=("$1"); shift;;
      x"--priv")     shift; privM+=("$1");     shift;;
      #
      x"--") shift;  ((1==$#)) || { echo "err: there should be exactly one positional parameter"; exit 1; }; break;;
      *)     echo "err: invalid parameter '$1'"; exit 1;;
    esac
  done

  if ! "$D"; then
    ((0==${#virtpubM[@]}))  || { echo "err: virtual method not allowed in final (non-derivable) type"; exit 1; }
    ((0==${#virtprivM[@]})) || { echo "err: virtual method not allowed in final (non-derivable) type"; exit 1; }
  fi

  [[ "$1" =~ ^(([0-9A-Za-z]+)::([0-9A-Za-z]+))$ ]] || help2
  [ -n "${BASH_REMATCH[2]}" ] || help2
  N="${BASH_REMATCH[2],,}"
  [ -n "${BASH_REMATCH[3]}" ] || help2
  T="${BASH_REMATCH[3],,}"
  TI="${N^}${T^}"
  C="${N^}${T^}Class"

  # pygmentize -l c <<<"$H"
  echo
  echo "/$(printf -- '*%.0s' {1..78})/"
  echo
  H_emit
  echo
  echo "/$(printf -- '*%.0s' {1..78})/"
  echo
  C_emit

}
