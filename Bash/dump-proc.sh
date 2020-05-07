#!/bin/sh

usage() {
    echo "$0 <process name>"
    echo "Wait until process starts and dump some files from /proc"
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

echo "# env:"
cat /proc/$progpid/environ
echo "# mounts:"
cat /proc/$progpid/mounts
echo "# status:"
cat /proc/$progpid/status
echo "# cmdline:"
cat /proc/$progpid/cmdline
