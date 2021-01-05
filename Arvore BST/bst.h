#ifndef _BST_H
#define _BST_H

// estrutura dos nó da arvore
typedef struct no {
    struct no *esq, *dir;
    int valor;
} no;

// função que ira inserir dados na arvore
no* inserir(no* raiz, int valor);

// função que remove dados da arvore
no* remover(no* raiz, int valor);

// função que imprimi a arvore em Pré-Order
void preorder(no* raiz);

// função que imprimi a arvore em In-Order
void inorder(no* raiz);

// função que imprimi a arvore em Pós-Order
void posorder(no* raiz);

// função que imprimi a arvore em modo reverso
void reverse(no* raiz);

// função que conta as raizes com par da arvore
int qntdPar(no* raiz);

// função que torna os nó de uma arvore em seus quadrados
no* quadrado(no* raiz);

// função que verifica se um valor é existente na arvore
int existe(no* raiz, int valor);

// calculo da altura da arvore
int altura(no* raiz);

// calculo da diferenca entra 2 inteiros
int max(int a, int b);

// contador de de elementos da arvore
int cont(no* raiz);

// somador de elemtos da arvore
int somar(no * raiz);



#endif