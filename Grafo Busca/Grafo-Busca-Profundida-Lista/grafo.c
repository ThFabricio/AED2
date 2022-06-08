#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// Criação e Inicializa do Grafo

grafo *criacaoGrafo (int tamanho){

	grafo *g = malloc(sizeof(grafo));

	g->tamanho = tamanho;

	g->mapa = (char *) malloc(sizeof(char)*tamanho);

	g->listAdj = malloc(tamanho * sizeof(listVertice));

	g->cor = malloc(sizeof(int)*(tamanho+1));

	int x;

	for(x=0; x < tamanho; x++){

		g->listAdj[x] = NULL;
		g->cor[x] = branco;
	}

	return g;
}

grafo *inicializarGrafo (grafo *g){

	FILE *arquivo;
	arquivo = fopen("entrada.txt", "r");

	int vertices, arestas, i;
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
		adicionarAresta(g, indiceGrafo(g, aresta1), indiceGrafo(g, aresta2));
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

void adicionarAresta(grafo *g, int v1, int v2){

	listVertice *novo = novoVertice(v2);
	novo->prox = g->listAdj[v1];
	g->listAdj[v1] = novo;

	novo = novoVertice(v1);
	novo->prox = g->listAdj[v2];
	g->listAdj[v2] = novo;

}

listVertice *novoVertice(int v){

	listVertice *novo = malloc(sizeof(listVertice));

	novo->vertice = v;
	novo->prox = NULL;
	return novo;
}

void imprimir(grafo* g){

    int x;

	printf("Lista Adjacente\n");

    for (x = 0; x < g->tamanho; x++){

        listVertice *p = g->listAdj[x];
        printf("%c", g->mapa[x]);

        while (p!=NULL){
            printf("-> %c", g->mapa[p->vertice]);
            p = p->prox;
        }
        printf("\n");
    }
    printf("\n");
}


// Busca em Largura

void dsf(grafo *g, int v){

	listVertice *lista = g->listAdj[v];
	listVertice *temp = lista;

	g->cor[v] = cinza;
	printf("Visitado: %c\n", g->mapa[v]);

	while (temp!=NULL){

		int ligacao = temp->vertice;

		if(g->cor[ligacao] == branco){

			dsf(g, ligacao);
		}

		temp = temp->prox;
	}
	
	g->cor[v] = preto;
}

void auxDSF(grafo*g, char vertice){

	int verticeBusca = indiceGrafo(g, vertice);

	if(vertice == -1){

		printf("O Vertice %c nao existe no Grafo", vertice);
	}
	else{

		printf("Busca em Produndidade feita a parti de: %c\n", vertice);
		dsf(g, verticeBusca);
	}
	
}



int main(int argc, int* argv) {

	grafo *g;
	
	g = inicializarGrafo(g);

	imprimir(g);

	auxDSF(g, 'A');

	return 0;

}
