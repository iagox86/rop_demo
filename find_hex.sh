#!/bin/bash

if [ $# -lt 2 ]; then
  echo "Usage: $0 <pattern> <files>"
  echo "(where <pattern> is a stream of hex bytes, such as '90 90 90')"
  exit
fi

PATTERN=$1
shift

RED=${txtbld}$(tput setaf 1)
RESET=$(tput sgr0)


while [ $1 ]; do
  FILE=$1
  echo -n "$FILE: "
  FILEDATA=`cat $FILE | xxd -i | tr -d '\n' | sed -e 's/ //g' -e 's/0x//g' -e 's/,/ /g'`
  if echo $FILEDATA | grep -i "$PATTERN" > /dev/null; then
    echo -n "Pattern found: "
    echo $FILEDATA | sed -r "s/^.*(.{16})($PATTERN)(.{16}).*$/\1$RED\2$RESET\3/"
  else
    echo "Pattern not found"
  fi

  shift
done


