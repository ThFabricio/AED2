#ifndef GRAFO_H
#define GRAFO_H

enum coloracao {branco, cinza, preto};

typedef struct listVertice{

	char *v;
	int vertice;
	struct listVertice * prox;
	
} listVertice;


typedef struct grafo {

	int tamanho;
	char *mapa;
	int *cor;
	listVertice ** listAdj;
} grafo;


typedef struct fila {
	
	int tamanhoFila;
	int *itens;
	int proximo;
	int anterior;
} fila;


// Funções referentes a Grafo
grafo *criacaoGrafo(int tamanho);
grafo *inicializarGrafo (grafo *g);
int indiceGrafo(grafo *g, char c);
void adicionarAresta(grafo *g, int v1, int v2);
void imprimir(grafo *g);

// Funções referentes a fila
fila *criarFila(int tamanho);
void enfileirar(fila *f, int valor);
int desenfileirar(fila *f);
void imprimirFila(fila *f, grafo *g);
int vazio(fila *f);


//Funções da Busca em Largura
void bsf(int vertice, fila *f, grafo *g);
void auxBSF(char vertice, fila *f, grafo*g);

#endif
