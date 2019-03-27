#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include <stdlib.h>
#include <stdio.h>
#define N 6

typedef struct Vertice{
	int rotulo, estimativa, ifFechado;
	struct Vertice *pai;
} vertice;

vertice create_vertice(int r, int e, vertice *p);

void dijkstra (int matriz[N][N], int inicial, int final);
void encontra_caminho (vertice abertos[N], int inicial, int final, int matriz[N][N]);

#endif /* DIJKSTRA_H_ */
