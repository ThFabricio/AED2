#ifndef GRAFO_H
#define GRAFO_H



typedef struct listVertice{

    char *v;
    int vertice;
	int peso;
    struct listVertice * prox;
} listVertice;

typedef struct grafo {

	int tamanho;
	char *mapa;
    int *visitado;
	listVertice ** listAdj;
} grafo;

typedef struct noHeap{

    int v;
    int chave;
}noHeap;

typedef struct heap{

    int tamanhoHeap;
    int capacidade;
    int *posicao;
    noHeap ** matriz;
}heap;


grafo *criarGrafo(int tamanho);
grafo *inicializarGrafo (grafo *g);
listVertice *novoVertice(int v, int peso);
void adicionarAresta(grafo *g, int v1, int v2, int peso);
void imprimirGrafo(grafo *g);
int indiceGrafo(grafo *g, char c);


heap *criarHeap(int cap);
noHeap *novoHeap(int v, int chave);
void trocar(noHeap **a, noHeap **b);
void heapficar(heap *h, int indice);
int vazio(heap *h);
noHeap *retirarHeap (heap *h);
void diminuirChave (heap *h, int v, int chave);
int existe(heap *h, int v);
void imprimir(int *arr, int n, grafo *g);
void prim(grafo *g);
int retornaPeso(grafo *g, int a, int b);


#endif
