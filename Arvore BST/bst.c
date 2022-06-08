#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

arvore inserir (arvore raiz, int valor) {
    //caso base
    if(raiz == NULL) {
        //alocar espaço em memória para o novo no
        no* novo = (no *) malloc(sizeof(no));

        //inicializar os valores do novo no
        novo->esq = NULL;
        novo->dir = NULL;
        novo->valor = valor;

        //fazer a ligação do nó com o restante da árvore
        return novo ;
    } else {
        if(valor > raiz->valor) {
            //caso recursivo inserir na sub-árvore direita
            raiz->dir = inserir(raiz->dir, valor);   
        } else {
            //caso recursivo inserir na sub-árvore esquerda
            raiz->esq = inserir(raiz->esq, valor);   
        }
        return raiz;	
    }
}

arvore remover (arvore raiz, int valor) {
    if(raiz == NULL)
        return NULL;

    if(raiz->valor == valor) {
        //caso 1 - zero filho
          if(raiz->esq == NULL && raiz->dir == NULL) {
                //free
                return NULL;
            }

        //caso 2a: quando possui um filho a direita, porem n possui a esquerda
        else if(raiz->esq == NULL && raiz->dir != NULL){

            no* retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        //caso 2b: Quando possui um filho a esquerda, porem nao a direita
        else if(raiz->esq != NULL && raiz->dir == NULL){

            no* retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

        //caso 3: quando possui dois filhos, um em sua esquerda e um a sua direita
        else{

            raiz->valor = procura(raiz->esq);
            raiz->esq = remover(raiz->esq, raiz->valor);
            return raiz;
        }
        //fazer uma função que retorna o valor do maior
    } else {
        if(valor < raiz->valor) {
            raiz->esq = remover(raiz->esq, valor);
        } else {
            raiz->dir = remover(raiz->dir, valor);
        }
    }
}

void preorder(arvore raiz) {
    if(raiz != NULL) {
           printf("[%d]", raiz->valor);
           preorder(raiz->esq);
           preorder(raiz->dir);
    } 
}

void inorder(arvore raiz) {
    if(raiz != NULL) {
           preorder(raiz->esq);
           printf("[%d]", raiz->valor);
           preorder(raiz->dir);
    } 
}

void posorder(arvore raiz) {
    if(raiz != NULL) {
           preorder(raiz->esq);
           preorder(raiz->dir);
           printf("[%d]", raiz->valor);
    } 
}

void reverse(arvore raiz){

    // Caso Base, raiz vazia
    if(raiz == NULL){

    }else{

        // Caso recursivo, quando a raiz da arvore esta preenchido

        // Passo 1: Percorrimento do lado direito da arvore
        reverse(raiz->dir);

        // Passo 2: Chamada para imprimir a raiz da arvore, na volta do perccorimento do lado direto
        printf("[%d]", raiz->valor);

        // Passo 3: Percorrimento do lado esquerdo da arvore
        reverse(raiz->esq);
    }


}

// função que procura se um numero e existente na arvore
int existe(arvore raiz, int valor){

    if(raiz == NULL){

        return 0;
    }
    else{

        if(raiz->valor == valor){

            return 1;
        }
        else {

            if(valor > raiz->valor){

                if(raiz->dir != NULL){

                    return existe(raiz->dir, valor);
                } 
                else{

                    return 0;
                }
            }
            if(valor < raiz->valor){

                if(raiz->esq != NULL){

                    return existe(raiz->esq, valor);
                } 
                else{

                    return 0;
                }
            }
        }
        
        return 0;
    }
}

void qntdPrimos (arvore raiz){

    int resultado, i, valor;

    if(raiz == NULL){

    }
    else{

        valor = raiz->valor;
        resultado = 0;
        
        for (i = 1; i <= valor; i++)
        {
            if(valor%i == 0){
                resultado ++;

            }
            if (resultado > 2)
            {
               break;
            }  
        }

        if(resultado <= 2){

            printf("%d \n", valor);
            qntdPrimos(raiz->dir);
            qntdPrimos(raiz->esq);
        }
        
    }
}

// função que reajusta a arvore
arvore reajustar(arvore raiz, int porcentagem){

    if(raiz == NULL){

    }
    else{

        raiz->valor += (raiz->valor*porcentagem)/100;
        reajustar(raiz->esq, porcentagem);
        reajustar(raiz->dir, porcentagem);
        return raiz;
    }
}

// função que procura o maior valor do lado esquerdo da arvore
int procura(arvore raiz){

    if(raiz == NULL){

    }
    else{

        if(raiz->dir != NULL){

            return procura(raiz->dir);
        }
        else{

            return raiz->valor;
        }
    }
}

