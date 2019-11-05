#!/bin/bash -e

storedir=gen-patches
i=0

mkdir -p $storedir || true
rm $storedir/* || true
cat > $storedir/series

# Input: git commit list
while read hash
do
    # Generate patch with index
    stri=$(printf %04d $i)
    git show -p $hash > $storedir/$stri.patch
    # Add patch to list
    echo "$i.patch" >> $storedir/series
    i=$((i+1))
done 
