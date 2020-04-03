#!/bin/bash


for i in log/*
do
	echo -n  "$i "
	grep solution $i | awk 'BEGIN { a=-1} {if(a<$8) a=$8} END {print a}'
done

