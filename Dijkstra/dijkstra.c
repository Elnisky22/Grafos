#include <stdlib.h>
#include <stdio.h>
#include "dijkstra.h"
#define N 6

//Gera um v�rtice do grafo
vertice create_vertice(int r, int e, vertice *p){
	vertice new_vertice;
	new_vertice.rotulo = r;
	new_vertice.estimativa = e;
	new_vertice.pai = p;
	new_vertice.ifFechado = 0;
	return new_vertice;
}

//Resolu��o do Algoritmo de Dijkstra
void dijkstra (int matriz[N][N], int inicial, int final){
	int qtdF = 0;
	vertice *abertos = malloc(N* sizeof(vertice));

	abertos[inicial] = create_vertice(inicial, 0, NULL);

	while (qtdF < N){
		//Verificar quem � o menor aberto do v�rtice e fecha
		vertice menor = abertos[N];
		for(int i = 0; i < N; i++){
			if ((abertos[i].estimativa < menor.estimativa) && (abertos[i].ifFechado = 0))
				menor = abertos[i];
		}
		abertos[menor.rotulo].ifFechado = 1;
		qtdF++;

		//Percorrer as conex�es do v�rtice de menor custo
		for (int j = 0; j < N; j++){
			if (matriz[abertos[menor.rotulo]][j] != 0){
				if (abertos[j] == NULL){ //Se o v�rtice n�o existir, gera
					abertos[j] = create_vertice(j, (abertos[matriz[abertos[menor.rotulo]][j]] + menor.estimativa), menor);
				}
				else if (abertos[j].ifFechado == 0){ //Se o v�rtice j� existir, checa se ele est� fechado
					//Se estiver aberto, verifica se a nova estimativa � menor que a existente
					//Se for menor, troca de pai
					if (abertos[j].estimativa > (abertos[matriz[abertos[menor.rotulo]][j]] + menor.estimativa)){
						abertos[j] = (abertos[matriz[abertos[menor.rotulo]][j]] + menor.estimativa);
						abertos[j].pai = menor;
					}
				}
			}
		}
	}
	encontra_caminho (abertos, inicial, final, matriz);
}

void encontra_caminho (vertice abertos[N], int inicial, int final, int matriz[N][N]){
	vertice *temp = abertos[final];

	while (temp != inicial){
		for (int j = 0; j < N; j++){
			if (matriz[temp->rotulo][j] != 0){
				if ((temp->estimativa - matriz[temp->rotulo][j]) == abertos[j]->estimativa){
					temp = abertos[j];
					printf ("%d -> ", abertos[j]->rotulo);
				}
			}
		}
	}
}
