#!/bin/sh

INDENT=`cat NOTES`

echo "using command: $INDENT <file>"

indent_files() {
	echo $INDENT $1
	$INDENT $1
}


indent_files libcsoap/*.c
indent_files libcsoap/*.h
indent_files nanohttp/*.c
indent_files nanohttp/*.h
indent_files examples/csoap/*.c

