#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

vector* new_vector(int qtd){
	vector *v = malloc (sizeof(vector));
	v->verify = malloc (sizeof(int) * qtd);
	v->qtd = 0;
	v->kappacidade = qtd;
	return v;
}

//adicionar uma chave ao vetor auxiliar
void add_vector(vector* v, int key){
	if (full_vector(v)){
		realloc_vector(v);
	}
	v->verify[v->qtd] = key;
	v->qtd++;
}

//buscar no vetor auxiliar se a jogada já foi realizada anteriormente
int search_vector(vector* v, int key){
	if (v == NULL){
		printf ("VETOR NULO\n");
		return 0;
	}

	for (int i = 0; i < v->qtd; i++){
		if (v->verify[i] == key){
			printf ("ENCONTRADO %d NA POSICAO %d\n", key, i);
			return 1;
		}
	}
	return 0;
}

//aumentar o tamanho do vetor auxiliar
void realloc_vector(vector* v){
	v->verify = realloc (v->verify, sizeof(int) * (v->kappacidade += 40));
	v->kappacidade = v->kappacidade + 40;
}

//checar se o vetor está cheio
int full_vector(vector* v){
	if (v->qtd == v->kappacidade) return 1;
	else return 0;
}
