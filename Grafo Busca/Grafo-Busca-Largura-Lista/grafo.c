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

listVertice *novoVertice(int v){

	listVertice *novo = malloc(sizeof(listVertice));

	novo->vertice = v;
	novo->prox = NULL;
	return novo;
}

void adicionarAresta(grafo *g, int v1, int v2){

	listVertice *novo = novoVertice(v2);
	novo->prox = g->listAdj[v1];
	g->listAdj[v1] = novo;

	novo = novoVertice(v1);
	novo->prox = g->listAdj[v2];
	g->listAdj[v2] = novo;

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



// Criação e Manipulação da Fila


fila *criarFila(int tamanho){

	fila *f = malloc(sizeof(fila));

	f->tamanhoFila = tamanho*10;
	f->itens = malloc(sizeof(int)*(tamanho*10));
	f->proximo = -1;
	f->anterior = -1;

	int aux;

	for(aux=0; aux<f->tamanhoFila; aux++){

		f->itens[aux] = 0;
	}

	return f;
}

void enfileirar(fila *f, int valor){

	if(f->anterior == f->tamanhoFila-1){

		printf("Overflow da fila\n");
	}
	else{

		if(f->proximo == -1){

			f->proximo = 0;
		}

		f->anterior++;
		f->itens[f->anterior] = valor;
	}
}

int desenfileirar(fila *f){

	int remover;

	if(vazio(f)){

		printf("Underflow da fila\n");
		exit(1);
	}

	remover = f->itens[f->proximo];
	f->proximo++;
	
	return remover;
}

int vazio(fila *f){

	if(f->proximo == -1 || f->proximo > f->anterior){
		return 1;
	}else{
		return 0;
	}
}

void imprimirFila(fila *f, grafo *g){

	int aux;

	if(vazio(f)){
		printf("fila vazia\n");
	}else{
		printf("fila: ");
		for(aux = f->proximo; aux<f->anterior+1; aux++){
			printf("%c ", g->mapa[f->itens[aux]]);
		}
		printf("\n");
	}
}


// Busca em Largura

void bsf(int vertice, fila *f, grafo *g){

	int aux;

	enfileirar(f, vertice);
	g->cor[vertice] = cinza;
	printf("Busca em Largura feita a parti de: %c\n", g->mapa[vertice]);

	imprimirFila(f, g);

	while (!vazio(f)){

		vertice = desenfileirar(f);
		g->cor[vertice] = preto;
		printf("Vertice visitada: %c\n", g->mapa[vertice]);

		for(aux = 0; aux<g->tamanho; aux++){

			if(g->listAdj[aux] != NULL && g->cor[aux] == branco){

				enfileirar(f, aux);
				g->cor[aux] = cinza;
			}
		}

		imprimirFila(f, g);
	}
	
	printf("\n");
}

void auxBSF(char vertice, fila *f, grafo*g){

	int verticeBusca = indiceGrafo(g, vertice);

	if(vertice == -1){

		printf("O Vertice %c nao existe no Grafo", vertice);
	}
	else{

		bsf(verticeBusca, f, g);
	}
	
}



int main(int argc, int* argv) {

	grafo *g;
	fila *f;

	g = inicializarGrafo(g);
	f = criarFila(g->tamanho);

	imprimir(g);

	auxBSF('R', f, g);

	return 0;

}
