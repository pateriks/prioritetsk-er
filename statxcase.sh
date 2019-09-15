#!/bin/bash
iterations=({10000..1000000..1000})
for val in ${iterations[@]}; do
	./list $val -1
	printf "\t"
	./list $val -2
	printf "\n"
done
