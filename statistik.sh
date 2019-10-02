#!/bin/bash
iterations=({1..500..5})
for val in ${iterations[@]}; do
	printf "$val\t"
	./skew $val
	printf "\t"
	./list $val
	printf "\n"
done
