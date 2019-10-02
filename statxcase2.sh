#!/bin/bash
iterations=({1000..10000..50})
for val in ${iterations[@]}; do
	./skew $val -1
	printf "\t"
	./skew $val -2
	printf "\n"
done
