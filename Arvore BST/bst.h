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

// calculo da altura da arvore
int altura(no* raiz);

// calculo da diferenca entra 2 inteiros
int max(int a, int b);

// contador de de elementos da arvore
int cont(no* raiz);

// somador de elemtos da arvore
int somar(no * raiz);

// função que procura o maior numero a esquerda de uma raiz
int maior(no* raiz);

#endif