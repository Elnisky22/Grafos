#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//criar a fila
void create_queue(){
	front = rear = NULL;
}

//enfileirar um valor
void enqueue(int valor){
	if (rear == NULL){
		rear = (struct nodef *) malloc (1*sizeof(struct nodef));
		rear->next = NULL;
		rear->key = valor;
		front = rear;
	}
	else{
		temp = (struct nodef *) malloc (1*sizeof(struct nodef));
		rear->next = temp;
		temp->key = valor;
		temp->next = NULL;
		rear = temp;
	}
}

//desenfileirar um valor
int dequeue(){
	front1 = front;

	if(front1 == NULL){
		printf("\nErro ao remover, a fila está vazia.\n");
		return -1;
	}
	else{
		int aux;
		if (front1->next != NULL){
			front1 = front1->next;
			aux = front->key;
			free(front);
			front = front1;
			return aux;
		}
		else{
			aux = front->key;
			free(front);
			front = NULL;
			rear = NULL;
			return aux;
		}
	}
}

int empty_queue(){
	return ((front == NULL) && (rear == NULL));
}

//imprimir a fila
void print_queue(){
	front1 = front;

	if ((front1 == NULL) && (rear == NULL)){
		printf ("\nFila vazia.\n");
		return;
	}
	while (front1 != rear){
		printf("%d ", front1->key);
		front1 = front1->next;
	}
	if (front1 == rear) printf ("%d", front1->key);
}
