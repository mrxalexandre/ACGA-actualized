#!/bin/bash

# dir com as instâncias
P=instancias


# dir log
log="log";
mkdir $log;

for i in $P/*
do
	j=$(basename $i);

	echo "Running at $i";
	# Se o arquivo de log já existe, ele não executa
	if [ -e ${log}/${j}.log ];
	then
		echo "File exist..";
	else
		# Executa cada experimento 10x
		for seed in `seq 1 10`
		do
			# Aqui vc colocar a execução, jogando o a saida para o log
			# Adaptar aos parâmetros. No caso tempo -T com 30s e
			# a semente -s seed
			./main < $i >> ${log}/${j}.log;
		done
	fi

done

