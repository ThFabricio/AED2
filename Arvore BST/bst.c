#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


// função de inserção de dados nos nó da arvore
no* inserir(no* raiz, int valor) {

    // caso base da recursão, raiz vazia
    // verificação se a raiz esta vazia
    if (raiz == NULL){

        // passo 1: alocação da memoria
        no *novo = (no *) malloc(sizeof(no));

        // passo 2: inicialização e inserção dos valores do nó
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;

        // passo 3: atualização do ponteiro
        return novo;

    } else
    {
        // casos recursivos
        // passo 1: verificação dos valores a serem inseridos
        // inserção na direita da raiz

        if (valor > raiz->valor){

            // passo 2: inserir o valor e novo nó, em seu devido "galho"
            // junto a inserção vem a atualização do ponteiro da raiz

            raiz->dir = inserir(raiz->dir, valor);
        } else{

            // passo 2: inserir o valor e novo nó, em seu devido "galho"
            // junto a inserção vem a atualização do ponteiro da raiz

            raiz->esq = inserir(raiz->esq, valor);
        }

        // retorno da raiz atualizada com suas modificações

        return raiz;  
    }
}

// função de remoção de dados da arvore
no* remover (no* raiz, int valor){

    //caso base: quando a raiz não foi inicializada
    if (raiz == NULL){

        return NULL;
    } 
    
    //funções de quando de quando é encontrado o valor que se deixa remover
    if(raiz->valor == valor){

        //caso1: quando o valor a ser removido eh o unico valor existente da raiz
        if(raiz->esq == NULL && raiz ->dir == NULL){

            free(raiz);
            return NULL;
        }

        //caso2: quando o valor da raiz a ser removido possui um filho a direita
        if(raiz->esq == NULL && raiz ->dir != NULL){

            no* retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        //caso2: quando o valor da raiz a ser removido possui um filho a esquerda
        if(raiz->esq != NULL && raiz ->dir == NULL){

            no* retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        //caso3: quando o valor da raiz a ser removido possui 2 filhos
        if(raiz->esq != NULL && raiz ->dir == NULL){

            raiz->valor = maior(raiz->esq);
            raiz = remover(raiz->esq, raiz->valor);
        }

    }
    
    //funções de procura do valor a se remover
    else
    {
        if (valor > raiz->valor){
            
            raiz->dir = remover(raiz->dir, valor);
        } else{

            raiz->esq = remover(raiz->esq, valor);
        }

        return raiz;  
    }

}

// Função de print da arvore em Pré-Order
// Em Pré=Order primeiro se imprime a raiz, depois pecorre os seus galhos

void preorder (no* raiz){

    // Caso Base, raiz vazia

    if(raiz == NULL){

    }else{

        // Caso recursivo, quando a raiz da arvore esta preenchido
        // Passo 1: chamada para imprimir a raiz da arvore

        printf("[%d]", raiz->valor);

        // Passo 2: chamada para imprimir toda a sub-arvore /galhos a esquerda da raiz

        preorder(raiz->esq);

        // Passo 3: chamada para imprimir toda a sub-arvore/galhos a direita da raiz

        preorder(raiz->dir);

    }
    
}

// Função que calcula a altura da arvore

int altura (no* raiz){

    // caso base da contagem
    if(raiz == NULL){
        return 0;

    // casos recursivos
    }else{
        
        return 1 + max(altura(raiz->esq), altura(raiz->dir));

    }
    
}

// Funcao que calcula o maior entre dois inteiros
int max(int a, int b){

    if(a > b){
        return a;
    } else{
        return b;
    }   
}

// Função que conta o numeros de elementos da arvore

int cont(no* raiz){

    if(raiz == NULL){
        return 0;
    } else
    {
        return 1 + cont(raiz->esq) + cont(raiz->dir);
    }
    
}

// Função que soma os elementos da arvore

int somar(no* raiz){

    if(raiz == NULL){
        return 0;
    } else
    {
        return raiz->valor + somar(raiz->esq) + somar(raiz->dir);
    }
    
}

// Função que calcula qual o maior valor a esquerda da arvore

int maior(no* raiz){

    // caso1: quando não ah mais valores a direita da raiz
    if((raiz->esq == NULL && raiz ->dir == NULL) || (raiz->esq != NULL && raiz->dir == NULL)){

        return raiz->valor;
    }
    if (raiz->esq == NULL && raiz ->dir != NULL){

        return maior(raiz->esq);
    }
}
