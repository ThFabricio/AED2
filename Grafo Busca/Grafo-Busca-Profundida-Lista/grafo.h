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

// Funções referentes a Grafo
grafo *criacaoGrafo(int tamanho);
grafo *inicializarGrafo (grafo *g);
int indiceGrafo(grafo *g, char c);
void adicionarAresta(grafo *g, int v1, int v2);
listVertice *novoVertice(int v);
void imprimir(grafo *g);

//Funções da Busca em Largura
void dsf(grafo *g, int v);
void auxDSF(grafo*g, char vertice);

#endif
