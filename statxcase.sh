#!/bin/bash
gcc list2.c -o list
iterations=({1000..10000..50})
for val in ${iterations[@]}; do
	./list $val -1
	printf "\t"
	./list $val -2
	printf "\n"
done
