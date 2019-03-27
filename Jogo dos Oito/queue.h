#ifndef QUEUE_H_
#define QUEUE_H_

//Estrutura da fila
struct nodef{
	int key;
	struct nodef *next;
} *front, *rear, *temp, *front1;

void create_queue();
void enqueue(int valor);
int dequeue();
int empty_queue();
void print_queue();

#endif /* QUEUE_H_ */
