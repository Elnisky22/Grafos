#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "queue.h"
#include "matriz.h"

int main(){

	printf("Matriz inicial:\n");
	int matriz[3][3], vet[9] = {1, 2, 3, 8, 6, 4, 7, 5, 0};
	fill(matriz, vet);
	print_matriz(matriz);

	printf("\nIniciando busca na matriz:\n");
	node *T = new_node(keyGenerator(matriz));
	busca_largura(T);

	return 0;
}
