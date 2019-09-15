#!/bin/bash
iterations=({10000..1000000..1000})
for val in ${iterations[@]}; do
	./skew $val -1
	printf "\t"
	./skew $val -2
	printf "\n"
done
