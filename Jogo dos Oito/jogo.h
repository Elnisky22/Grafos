#ifndef JOGO_H_
#define JOGO_H_

//Estrutura da árvore
typedef struct node{
	int key;
	struct node *right;
	struct node *left;
	struct node *up;
	struct node *down;
} node;

//**************FUNÇÕES DO JOGO*******************
int rightEmpty(int key);
int leftEmpty(int key);
int upEmpty(int key);
int downEmpty(int key);
//*************FIM FUNÇÕES DO JOGO***************

//*************FUNÇÕES DA ÁRVORE********************
node* new_node(int valor);
void busca_largura(node *T);
//*************FIM FUNÇÕES DA ÁRVORE****************

#endif /* JOGO_H_ */
