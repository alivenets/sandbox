#!/bin/bash

usage() {
    echo "Usage: $0 <output filename>"
}

FILENAME=$1
if [ -z "$FILENAME" ]; then
    usage
    exit 1
fi

GIT_REV="$(git rev-parse HEAD)$(git diff --quiet HEAD || echo "+")"
GIT_BRANCH="$(git rev-parse --abbrev-ref HEAD)"

echo "Generate Git macros"

echo "
const char GIT_BRANCH[] = \"$GIT_BRANCH\";

const char GIT_REV[] = \"$GIT_REV\";
" > $FILENAME
