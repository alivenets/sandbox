#!/bin/sh

X86_64_LIB_DIR_NAME="x86_64-linux-gnu"
X86_64_DIR_LIST="/usr/local/lib/$X86_64_LIB_DIR_NAME /lib/$X86_64_LIB_DIR_NAME /usr/lib/$X86_64_LIB_DIR_NAME"

for dir_name in $X86_64_DIR_LIST
do
    echo "Dir: $dir_name"
done