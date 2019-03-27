#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "queue.h"
#include "matriz.h"
#include "vector.h"

node* new_node(int valor){
	node *T = malloc (sizeof(node));
	T->key = valor;
	T->right = NULL;
	T->left = NULL;
	T->up = NULL;
	T->down = NULL;
	return T;
}

//percorrer a árvore
void busca_largura(node *T){
	if (T == NULL) return;

	//criar a fila
	printf("Criando fila...\n");
	create_queue();
	printf("Enfileirando %d...\n", T->key);
	enqueue(T->key);

	//criar o vetor auxiliar
	vector *v = new_vector(40);

	//fazer a busca
	while(!empty_queue()){
		int busca = dequeue();
		printf ("\nRetirado %d da fila.\n", busca);
		int estado[3][3];
		fill(estado, keyDegenerator(busca));
		print_matriz(estado);

		if (busca == 123804765){
			printf ("Resultado encontrado.\n");
			break;
		}

		int r = rightEmpty(busca), l = leftEmpty(busca), u = upEmpty(busca), d = downEmpty(busca);
		printf ("DIREITA %d | ESQUERDA %d | CIMA %d | BAIXO %d\n", r, l, u, d);

		if (r != 0){
			if (!search_vector(v, r)){
				printf ("Jogada a direita encontrada.\n");
				add_vector(v, busca);
				T->right = new_node(r);
				printf ("Enfileirando %d...\n", T->right->key);
				enqueue(T->right->key);
			}
		}
		if (l != 0){
			if (!search_vector(v, l)){
				printf ("Jogada a esquerda encontrada.\n");
				add_vector(v, busca);
				T->left = new_node(l);
				printf ("Enfileirando %d...\n", T->left->key);
				enqueue(T->left->key);
			}
		}
		if (u != 0){
			if (!search_vector(v, u)){
				printf ("Jogada acima encontrada.\n");
				add_vector(v, busca);
				T->up = new_node(u);
				printf ("Enfileirado %d...\n", T->up->key);
				enqueue(T->up->key);
			}
		}
		if (d != 0){
			if (!search_vector(v, d)){
				printf ("Jogada abaixo encontrada.\n");
				add_vector(v, busca);
				T->down = new_node(d);
				printf ("Enfileirado %d...\n", T->down->key);
				enqueue(T->down->key);
			}
		}
	}
}

//testar se a jogada à direita é possível e gera a key referente
int rightEmpty(int key){
	int estado[3][3];
	fill(estado, keyDegenerator(key));
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (j-1 > 0){
				if (estado[i][j-1] == 0){
					estado[i][j-1] = estado[i][j];
					estado[i][j] = 0;
					return keyGenerator(estado);
				}
			}
		}
	}
    return 00000000;
}

//testar se a jogada à esquerda é possível e gera a key referente
int leftEmpty(int key){
	int estado[3][3];
	fill(estado, keyDegenerator(key));
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (j+1 < 3){
				if (estado[i][j+1] == 0){
					estado[i][j+1] = estado[i][j];
					estado[i][j] = 0;
					return keyGenerator(estado);
				}
			}
		}
	}
	return 00000000;
}

//testar se a jogada acima é possível e gera a key referente
int upEmpty(int key){
	int estado[3][3];
	fill(estado, keyDegenerator(key));
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (i+1 < 3){
				if (estado[i+1][j] == 0){
					estado[i+1][j] = estado[i][j];
					estado[i][j] = 0;
					return keyGenerator(estado);
				}
			}
		}
	}
	return 00000000;
}

//testar se a jogada abaixo é possível e gera a key referente
int downEmpty(int key){
	int estado[3][3];
	fill(estado, keyDegenerator(key));
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (i-1 >= 0){
				if (estado[i-1][j] == 0){
					estado[i-1][j] = estado[i][j];
					estado[i][j] = 0;
					return keyGenerator(estado);
				}
			}
		}
	}
	return 00000000;
}
