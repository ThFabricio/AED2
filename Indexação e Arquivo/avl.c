#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

extern char* strdup(const char*);

void inicializar(arvore *raiz) {
	*raiz = NULL;
}

int inicializarTabela(tabela *tab){

	inicializar(&tab->indice);
	tab->arquivo_dados = fopen("dados.txt", "a+");
	tab->indice = carregar_arquivo ("indice.dat", tab->indice);
	
	if(tab->arquivo_dados != NULL){

		return 1;
	}else{

		return 0;
	}

}

void finalizarTabela(tabela *tab){

	fclose(tab->arquivo_dados);
	salvar_arquivo("indice.dat", tab->indice);
}

dado *ler_dado(){

	dado *novo = (dado *) malloc(sizeof(dado));
	char *buffer = (char *) malloc(sizeof(256 * sizeof(char)));
	int aux;

	getchar();


	printf("Titulo: ");
	fgets(buffer, 255, stdin);
	tirar_enter(buffer);
	novo->titulo = strdup(buffer);

	printf("Autor: ");
	fgets(buffer, 255, stdin);
	tirar_enter(buffer);
	novo->autor = strdup(buffer);

	printf("Ano: ");
	fgets(buffer, 255, stdin);
	tirar_enter(buffer);
	novo->ano = strdup(buffer);

	printf("Codigo: ");
	scanf("%d", &novo->codigo);
	free(buffer);

	return novo;

}

void adicionarLivro(tabela *tab, dado *livro){

	if(tab->arquivo_dados != NULL){

		int cresceu;

		fseek(tab->arquivo_dados, 0L, SEEK_END);

		tipo_dado *novo = (tipo_dado *) malloc(sizeof(tipo_dado));
		novo->chave = livro->codigo;
		novo->indice = ftell(tab->arquivo_dados);

		fprintf(tab->arquivo_dados, "%d|%s|%s|%s|", livro->codigo, livro->titulo, livro->autor, livro->ano);
		tab->indice = adicionar(novo, tab->indice, &cresceu);
	}
}

void tirar_enter(char *string){

	string[strlen(string)-1] = '\0';
}

void salvar_arquivo(char *nome, arvore a){

	FILE *arq;
	arq = fopen(nome, "wb");
	
	if(arq != NULL){

		salvar_auxiliar(a, arq);
		fclose(arq);
	}
}

void salvar_auxiliar(arvore raiz, FILE *arq){

	if(raiz != NULL){

		fwrite(raiz->dado, sizeof(tipo_dado), 1, arq);
		salvar_auxiliar(raiz->esq, arq);
		salvar_auxiliar(raiz->dir, arq);
	}
}

arvore carregar_arquivo(char *nome, arvore a){

	FILE *arq;
	arq = fopen(nome, "rb");
	tipo_dado *temp;

	if(arq != NULL){

		int creceu;
		temp = (tipo_dado *) malloc (sizeof(tipo_dado));

		while (fread(temp, sizeof(tipo_dado), 1, arq)){

			a = adicionar(temp, a, &creceu);
			temp = (tipo_dado *) malloc(sizeof(tipo_dado));
		}

		fclose(arq);
	}

	return a;
}

void buscar_livro(int codigo, arvore raiz, tabela *tab){

	if(raiz != NULL){

		if(raiz->dado->chave == codigo){

			imprimir_elemento(raiz, tab);
		}
		else if (raiz->dado->chave > codigo){

			buscar_livro(codigo, raiz->esq, tab);
		}
		else{

			buscar_livro(codigo, raiz->dir, tab);
		}
	}
}



// CODIGO DA AVL
/*----------
Adiciona um novo elemento à árvore e realiza as operações de balanceamento, se necessário
Parâmetros:
    valor   - elemento a ser inserido
    raiz    - raiz da árvore onde o elemento será inserido
    cresceu - variável de controle que ajuda a calcular o fator de balanço

Retorno:
    Raiz da árvore resultante da operação de adicionar
--*/

arvore adicionar (tipo_dado *valor, arvore raiz, int *cresceu) {
    //Caso base da recursão: ou a árvore está vazia ou chegou em uma folha
	if(raiz == NULL) {
		arvore novo = (arvore) malloc(sizeof(struct no_avl));
		novo->dado = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;
	  * cresceu = 1; 
		return novo;
	}

    //Casos recursivos, se a raiz (relativa) não for NULL,        
    //acrescenta-se o elemento na sub-árvore direita ou esquerda,
    //dependendo do valor a ser inserido. Elementos maiores vão 
    //para direita, menores para esquerda.
	if(valor->chave > raiz->dado->chave) {
        //Elemento maior => adicionar na direita
		raiz->dir = adicionar(valor, raiz->dir, cresceu);
        //Após adicionar o elemento na direita, 
        //verifica se a sub-árvore da direita cresceu.
        //Em caso afirmativo, ajusta-se o fator de balanço 
        //da raiz relativa
        if(*cresceu) {
            //Chegando neste ponto, sabe se que:
            //a) O elemento foi inserido na sub-árvore direita; e
            //b) A sub-árvore a direita cresceu
			switch(raiz->fb) {
				case 0:
					raiz->fb = 1;
                    *cresceu = 1;
					break;
			    case -1:
					raiz->fb = 0;
					*cresceu = 0;
					break;
				case 1:
					*cresceu = 0;
                    //o fator de balanço passaria ao valor 2,
					return rotacionar(raiz);
					break;
			}
		}

	} else {
       //Elemento menor que raiz relativa, fazer o caso simétrico

	   raiz->esq = adicionar(valor, raiz->esq, cresceu);

	   if(*cresceu){

            switch (raiz->fb){

                case 0:

                    raiz->fb = -1;
                    *cresceu = -1;
                    break;

                case 1:

                    raiz->fb = 0;
                    *cresceu = 0;
                    break;

                case -1:

                    *cresceu = 0;
                    return rotacionar(raiz);
                    break;
            }
		}
	}
    //Se tirar isso, caga a árvore toda
	return raiz;
}

/*----------
Verifica o tipo de rotação que deve ser aplicado para reajustar a árvore
Parâmetros:
    raiz - pivô (ou raiz da sub-árvore que se encontra 
    com o |fb| = 2 ) 
Retorno:
    raiz da sub-árvore resultante
---*/
arvore rotacionar(arvore raiz) {
    //fb maior que zero => rotação esquerda
	if(raiz->fb > 0) {
		switch(raiz->dir->fb) {
            //o zero "conta" como rotação simples. 
            //Só ocorre no remover
			case 0:

			case 1:
				return rotacao_simples_esquerda(raiz);
			case -1:
				return rotacao_dupla_esquerda(raiz);					
			} 
	} else {
    //implementar o simétrico

		switch (raiz->esq->fb)
        {
            
            case 0:

                return rotacao_simples_direita(raiz);

            case 1:

                return rotacao_dupla_direita(raiz);

            case -1:

                return rotacao_simples_direita(raiz);
        }
	}
}

/*----------
Só está implementada a "base" do remover da BST.
Incluir a variável de controle "diminuir" similar a "cresceu do adicionar.
------*/
arvore remover (int valor, arvore raiz, int *diminuiu) {
	if(raiz == NULL) 
		return NULL;
	
	if(raiz->dado->chave == valor) {

		arvore retorno;

        if(raiz->esq != NULL && raiz->dir != NULL) {
            //procurar o maior elemento da sub-arvore a esquerda
            //atribuir esse valor ao dado da raiz relativa
            //chamar recursivamente o remover para eliminar o valor duplicado na sub-árvore esquerda

			raiz->dado = maior_elemento_esquerda(raiz->esq);
			raiz->esq = remover(valor, raiz->esq, diminuiu);
			if(*diminuiu) {
                switch(raiz->fb) {
                    case -1:

						raiz->fb = 0;
						*diminuiu = 1;
						break;

                    case 0:
                        raiz->fb = 1;
                        *diminuiu = 0;
						break;
                    case 1:

						raiz->fb = 2;
                        if(raiz->dir->fb==0){
                            *diminuiu= 0;
                        }else{
                            *diminuiu= 1;

                        }
                        return rotacionar(raiz);

                }
			}
			
        }		
		if(raiz->esq == NULL && raiz->dir != NULL ) {

			retorno =  raiz->dir;
			free(raiz);
			return retorno;
		}
		if(raiz->dir == NULL && raiz->esq != NULL) {

			retorno = raiz->esq;
			free(raiz);
			return retorno;
		}
		else{

			free(raiz);
			return NULL;
		}
		
	}	

	if(valor > raiz->dado->chave) {
			raiz->dir = remover(valor, raiz->dir, diminuiu);
           //verifica se a árvore diminuiu e ajusta os fatores de balanço
            if(*diminuiu) {
                switch(raiz->fb) {

                    case -1:

						raiz->fb = -2;
						if(raiz->esq->fb == 0){
							*diminuiu = 0;
						}
						else{
							*diminuiu = 1;
						}
                        rotacionar(raiz);
						break;

                    case 0:
                        raiz->fb = -1;
                        *diminuiu = 0;
						break;
                    case 1:
                        raiz->fb = 0;                        
                        *diminuiu = 1; 
						break;                       
                }

            }
	} 

	else {
			raiz->esq = remover(valor, raiz->esq, diminuiu);

			if(*diminuiu){

				switch (raiz->fb){

				case 1:

					raiz->fb = 2;
                    if(raiz->dir->fb == 0){
                        *diminuiu = 0;
                    }
                    else{
                        *diminuiu = 1;
                    }
                    rotacionar(raiz);

				case 0:
					
					raiz->fb = 1;
					*diminuiu = 0;
					break;

				case -1:

					raiz->fb = 0;
					*diminuiu = 1;

				}
			}
	}

	return raiz;

}

/*-------
Realiza a rotação simples esquerda sobre o pivô "raiz" e 
retorna a raiz relativa da árvore resultante 

      p
     / \
    t1  u
       / \
      t2 t3

     =>

      u
     / \
    p  t3
   / \
  t1 t2


-------*/
arvore rotacao_simples_esquerda(arvore raiz) {
	arvore p, u, t1, t2, t3;
    //inicializa os ponteiros
	p = raiz;
	u = raiz->dir;
    t1 = p->esq;
    //t2 e t3 não estão sendo modificados. 
    //só estão aqui por questões didáticas
    t2 = u->esq;
    t3 = u->dir;

    //Atualiza os ponteiros
	p->dir = t2;
	u->esq = p;
    
    //Atualiza os fatores de balanço de acordo com o fb de u
    //Esses valores vieram dos cálculos demonstrados na aula
	if(u->fb == 1) {
		p->fb = 0;
		u->fb = 0;
	} else {
		p->fb = 1;
		u->fb = -1;
	}	
    
    //Retorna a raiz da sub-árvore resultante, ou seja "u".
	return u;
}

arvore rotacao_dupla_esquerda(arvore raiz) {
    arvore p, u, v, t1, t2, t3, t4;
    //configuração inicial
    p = raiz;
    u = p->dir;
    v = u->esq;
    t1 = p->esq;
    t2 = v->esq;
    t3 = v->dir;
    t4 = u->dir;

    //configuração final
    v->esq = p;
    p->dir = t2;
    v->dir = u;
    u->esq = t3;

    //Atualizar os fb
    switch(v->fb) {
        case -1:
               break;
        case 0:

               break;
        case 1:
               break;
    }

    return v;
}

arvore rotacao_simples_direita(arvore raiz) {

	arvore p, u, t2;
    // passo 1
    p = raiz;
    u = raiz->esq;
	t2= u->dir;
	
	p->esq = t2;
	u->dir = p;

	if(u->fb== -1) {
		p->fb= 0;
		u->fb = 0;
	} else {
		p->fb = -1;
		u->fb = 1;
	}

	return u;
}

arvore rotacao_dupla_direita(arvore raiz) {


	arvore p, u, v;
    p = raiz;
    u = raiz->esq;
	v = u->dir;

	u->dir = v->esq;
	v->esq = u;
	p->esq = v->dir;
	v->dir = p;

	if(v->fb == -1){
		p->fb= 1;
		v->fb= 0;
	}else{
		p->fb = 0;
	}
	if(v->fb == 1){
		u->fb = -1;
		v->fb = 0;
	}else{
		u->fb = 0;
	} 

	return v;
}



/*---
Imprime a árvore de modo a facilitar a visualização da estrutura, incluindo também o fator de balanço.
---*/
void imprimir(arvore raiz) {
	printf("(");
	if(raiz != NULL) {
		//imprimir_elemento(raiz);
		imprimir(raiz->esq);
		imprimir(raiz->dir);
	}
	printf(")");
}

/*---
Auxiliar de imprimir
---*/
void imprimir_elemento(arvore raiz, tabela *tab) {

	dado * temp = (dado *) malloc (sizeof(dado));
    int contador_barras = 0;
    char *buffer = malloc(sizeof(char)*256);

	fseek(tab->arquivo_dados, raiz->dado->indice, SEEK_SET);
    
	while(1){
        fscanf(tab->arquivo_dados, "%c", buffer);
        if(buffer[0] == '|'){
            contador_barras++;
            if(contador_barras==4){
                printf("\n");
                break;
            }else{
                printf(", ");
                continue;
            }
        }
        printf("%c", buffer[0]);
    }

	free(buffer);
}






int altura(arvore raiz) {
	if(raiz == NULL) {
		return 0;
	}
	return 1 + maior(altura(raiz->dir), altura(raiz->esq));
}

int maior(int a, int b) {
	if(a > b)
		return a;
	else
		return b;
}

tipo_dado *  maior_elemento(arvore raiz) {

	if(raiz->dir == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->dir);
}

tipo_dado *  menor_elemento(arvore raiz) {

	if(raiz->esq == NULL)
			return raiz->dado;
	else
			return maior_elemento(raiz->esq);
}

void pre_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		imprimir_elemento(raiz, tab);
		pre_order(raiz->esq, tab);
		pre_order(raiz->dir, tab);
	}
}

void pos_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		pos_order(raiz->esq, tab);
		pos_order(raiz->dir, tab);
		imprimir_elemento(raiz, tab);
	}
}

void in_order(arvore raiz, tabela *tab) {
	if(raiz != NULL) {
		in_order(raiz->esq, tab);
		imprimir_elemento(raiz, tab);
		in_order(raiz->dir, tab);
	}
}


tipo_dado * maior_elemento_esquerda (arvore raiz){

	if(raiz->dir == NULL){
		return raiz->dado;
	}else{
		return maior_elemento_esquerda(raiz->dir);
	}
}