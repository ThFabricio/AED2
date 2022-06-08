#ifndef BST_H
#define BST_H

typedef struct no {
    int valor;
    struct no *esq, *dir;
} no;

typedef no* arvore;

arvore inserir (arvore raiz, int valor);

arvore remover (arvore raiz, int valor);

void preorder(arvore raiz);

// função que imprimi a arvore em In-Order
void inorder(arvore raiz);

// função que imprimi a arvore em Pós-Order
void posorder(arvore raiz);

// função que imprimi a arvore em modo reverso
void reverse(arvore raiz);

// função que conta a quantidade de Primos na arvore
void qntdPrimos(arvore raiz);

// função que reajusta a arvore
arvore reajustar(arvore raiz, int porcentagem);

// função que verifica se um valor é existente na arvore
int existe(arvore raiz, int valor);

// função de procura do maior valor do lado esquerdo
int procura(arvore raiz);


#endif
