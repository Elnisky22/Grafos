#ifndef JOGO_H_
#define JOGO_H_

//Estrutura da �rvore
typedef struct node{
	int key;
	struct node *right;
	struct node *left;
	struct node *up;
	struct node *down;
} node;

//**************FUN��ES DO JOGO*******************
int rightEmpty(int key);
int leftEmpty(int key);
int upEmpty(int key);
int downEmpty(int key);
//*************FIM FUN��ES DO JOGO***************

//*************FUN��ES DA �RVORE********************
node* new_node(int valor);
void busca_largura(node *T);
//*************FIM FUN��ES DA �RVORE****************

#endif /* JOGO_H_ */
