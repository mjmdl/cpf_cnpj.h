#!/usr/bin/sh

CC="gcc"
CFLAGS="-Wall -Wextra -Wpedantic -Werror"
SRCS="cpfnpj.c"
TARGET="cpfnpj"

$CC $CFLAGS -o $TARGET $SRCS
