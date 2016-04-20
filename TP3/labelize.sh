#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] 
then
    echo "usage $0 src ext"
    exit 1
fi

IMAGES=`find $1 -name "*.$2"`
for i in $IMAGES
do
    echo "$i;-2"
done
