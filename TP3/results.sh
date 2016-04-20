#!/bin/bash

make

LOOP=10

for i in {10..200..10}
do
    echo "$i 3500"
    for (( c=1; c<=$LOOP; c++ ))
    do
        ./main at.txt $i 3500 other.txt
    done
    echo ""
done

for i in {2000..4000..100}
do
    echo "50 $i"
    for (( c=1; c<=$LOOP; c++ ))
    do
        ./main at.txt 50 $i other.txt
    done
    echo ""
done
