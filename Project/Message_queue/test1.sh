#!/bin/bash

counter=1
echo test1

while [ $counter -le 10 ]
do
    make insmod
    make rmmod
    ((counter++))
done

echo test1 done