#!/bin/sh

ffmpeg -fflags +genpts -i $1 -strict experimental -vf scale=640:360 -r 24 $2
