#!/bin/sh

usage() {
    echo "$0 <process name>"
    echo "Wait for the process to start and connect to it via GDB"
}

progstr=$1
if [ -z "$progstr" ]; then
    usage
    exit 1
fi

progpid=$(pgrep -o $progstr)

while [ "$progpid" = "" ]; do
    progpid=$(pgrep -o $progstr)
done

gdb -ex continue -p $progpid
