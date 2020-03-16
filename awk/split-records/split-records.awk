#!/usr/bin/awk -f

{
    if (NR % 6 == 1)
        print "line",$2
    else {
        print
        if (NR % 6 == 0)
            print "#####"
    }
}