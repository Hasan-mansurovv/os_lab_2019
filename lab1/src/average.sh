#!/bin/bash

exec 0<numbers

average=0
count=0

while read number
do

average=$(($average+$number))
count=$(($count+1))

done

average=$(($average/$count))

echo "Среднее значение= $average" 
echo "Число элементов= $count"