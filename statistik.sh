#!/bin/bash
gcc skew2.c -o skew
gcc list2.c -o list
iterations=({1..500..5})
for val in ${iterations[@]}; do
	printf "$val\t"
	./skew $val
	printf "\t"
	./list $val
	printf "\n"
done
