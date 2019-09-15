#!/bin/bash
iterations=({1..1000..10})
for val in ${iterations[@]}; do
	./skew $val
	printf "\t"
	./list $val
	printf "\n"
done
