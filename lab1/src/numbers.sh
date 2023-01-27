#!/bin/bash


exec 3>numbers


for i in {1..150}

do

  

  (od -A n -t d -N 1 /dev/random)>&3

done

echo "Done!!!"