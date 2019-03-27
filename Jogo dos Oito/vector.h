#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct vector{
	int *verify;
	int qtd;
	int kappacidade;
} vector;

vector* new_vector(int qtd);
void add_vector(vector* v, int key);
int search_vector(vector* v, int key);
void realloc_vector(vector* v);
int full_vector(vector* v);

#endif /* VECTOR_H_ */
