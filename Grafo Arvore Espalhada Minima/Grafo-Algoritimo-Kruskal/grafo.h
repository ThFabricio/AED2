#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo {

	int tamanho;
	char *mapa;
	int **matriz;
} grafo;

typedef struct aresta{

	char u;
	char v;
	int peso;
} aresta;

typedef struct listAresta{

	aresta arestas[100];
	int quantidade;
} listAresta;


// Funções remetente a criação e manipulação de Grafo
grafo *criacaoGrafo(int tamanho);
grafo *inicializarGrafo (grafo *g);
int indiceGrafo(grafo *g, char c);
void adicionarAresta(grafo *g, int v1, int v2, int peso);
void imprimirGrafo(grafo *g);


// Kruskal
void ordernacaoPeso(listAresta *list);
int vertPos (int pertence[], int vert);
void uniaovert (grafo *g, int *pertence, int v1, int v2);
void kruskal(grafo *g);
void imprimir(grafo *g, listAresta *la);

#endif
