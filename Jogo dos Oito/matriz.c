#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

//preencher uma matriz
void fill(int matriz[3][3], int ordem[9]){
	int count = 0;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			matriz[i][j] = ordem[count];
			count++;
		}
	}
}

//gerar uma chave única a partir de uma matriz
int keyGenerator(int matriz[3][3]){
	int key = 0, count = 100000000;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			key = (key + (count * matriz[i][j]));
			count = count/10;
		}
	}
	return key;
}

//gerar um vetor a partir da chave
int *keyDegenerator(int key){
	int *v = (int *) malloc (sizeof(int) * 9);

	for(int i = 8; i >= 0; i--) {
		v[i]= key%10;
		key = key/10;
	}
	return v;
}

//imprimir uma matriz
void print_matriz(int matriz[3][3]){
	for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				printf ("%d ", matriz[i][j]);
			}
			printf ("\n");
		}
}
