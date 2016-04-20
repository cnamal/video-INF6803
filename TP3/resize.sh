#!/bin/bash

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ] || [ -z "$4" ]
then
    echo "usage $0 src ext width height"
    exit 1
fi

IMAGES=`find $1 -name "*.$2"`
for i in $IMAGES
do
    convert $i -resize $3x$4! $i
done
