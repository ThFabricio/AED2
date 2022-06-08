#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"


//Funções Referentes a Criação e Manipulação de Grafos

grafo *criacaoGrafo (int tamanho){

	grafo *g = malloc(sizeof(grafo));

	g->tamanho = tamanho;
	g->mapa = (char *) malloc(sizeof(char)*tamanho);
	g->matriz = (int **) malloc(sizeof(int *)*tamanho);

	int x, y;

	for(x=0; x<tamanho; x++){

		g->matriz[x] = (int *) malloc(sizeof(int)*tamanho);
	}
	
	for(x=0; x<tamanho; x++){

		for(y=0; y<tamanho; y++){

			g->matriz[x][y];
		}
	}

	return g;
}

grafo *inicializarGrafo (grafo *g){

	FILE *arquivo;
	arquivo = fopen("entrada.txt", "r");

	int vertices, arestas, i, peso;
	char aresta1, aresta2, c;

	fscanf(arquivo, "%d %d", &vertices, &arestas);

	g = criacaoGrafo(vertices);

	for(i=0; i<vertices; i++){

		c=fgetc(arquivo);
		g->mapa[i] = fgetc(arquivo);
	}

	for(i = 0; i<arestas; i++){
		c = fgetc(arquivo);
		aresta1 = fgetc(arquivo);
		aresta2 = fgetc(arquivo);
		fscanf(arquivo, "%d", &peso);
		adicionarAresta(g, indiceGrafo(g, aresta1), indiceGrafo(g, aresta2), peso);
	}

	fclose(arquivo);
	return g;

}

int indiceGrafo (grafo *g, char c){

	int x;
	
	for(x=0; x<g->tamanho; x++){

		if(c == g->mapa[x]){

			return x;
		}
	}
	return -1;
}

void adicionarAresta(grafo *g, int v1, int v2, int peso){

	g->matriz[v1][v2] = peso;
	g->matriz[v2][v1] = peso;

}

void imprimirGrafo(grafo *g) {
	
	int x,y;

	printf("Representação Matricial\n");

	for(x=0; x<g->tamanho; x++){

		if(x==0){

			printf(" ");
		}

		printf(" %c", g->mapa[x]);
	}

	printf("\n");

	for(x=0; x<g->tamanho; x++){

		printf("%c ", g->mapa[x]);

		for(y=0; y<g->tamanho; y++){

			printf("%d ", g->matriz[x][y]);
		}

		printf("\n");
	}

	printf("\n");
}


// Kruskal

void ordernacaoPeso(listAresta *list){

	int x, y;

	aresta aux;

	for(x=0; x<list->quantidade; x++){

		for(y=0; y<list->quantidade-1; y++){

			if(list->arestas[y].peso > list->arestas[y+1].peso){

				aux = list->arestas[y+1];
				list->arestas[y+1] = list->arestas[y];
				list->arestas[y] = aux;
			}
		}
	}
}

int vertPos (int pertence[], int vert){

	return pertence[vert];
}

void uniaovert (grafo *g, int *pertence, int v1, int v2){

	int x;

	for(x=0; x<g->tamanho; x++){

		if(pertence[x] == v2){

			pertence[x] = v1;
		}
	}
}

void kruskal(grafo *g){

	int pertence[g->tamanho];

	int x, y, v1, v2, va, vb;

	aresta aux;

	listAresta *list = (listAresta*) malloc(sizeof(listAresta));
	listAresta *la = (listAresta*) malloc(sizeof(listAresta));

	list->quantidade = 0;
	la->quantidade = 0;

	for(x = 1; x<g->tamanho; x++){

		for(y=0; y<x; y++){

			if(g->matriz[x][y] != 0){

				aux.peso = g->matriz[x][y];
				aux.u = g->mapa[x];
				aux.v = g->mapa[y];
				list->arestas[list->quantidade] = aux;
				list->quantidade++;
			}
		}
	}

	ordernacaoPeso(list);

	for(x = 0; x<g->tamanho; x++){

		for(y = 0; y<g->tamanho; y++){

			g->matriz[x][y] = 0;
			g->matriz[y][x] = 0;
		}
	}

	for(x=0; x<g->tamanho; x++){

		pertence[x] = x;
	}

	for(x = 0; x<list->quantidade; x++){

		v1 = indiceGrafo(g, list->arestas[x].u);
		v2 = indiceGrafo(g, list->arestas[x].v);
		va = vertPos(pertence, v1);
		vb = vertPos(pertence, v2);

		if(va != vb){

			adicionarAresta(g, v1, v2, list->arestas[x].peso);
			la->arestas[la->quantidade] = list->arestas[x];
			la->quantidade = la->quantidade+1;
			uniaovert(g, pertence, va, vb);
		}
	}
	imprimirGrafo(g);
	imprimir(g, la);
}

void imprimir(grafo *g, listAresta *la){

	int custo, x;
	custo = 0;

	for(x=0; x<g->tamanho-1; x++){

		printf("%c - %c : %d\n", la->arestas[x].u, la->arestas[x].v, la->arestas[x].peso);
		custo += la->arestas[x].peso;
	}
	printf("custo minimo: %d\n", custo);
}

int main(int argc, int* argv) {

	grafo * g;
	
	g = inicializarGrafo(g);

	kruskal(g);
}
