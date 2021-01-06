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
        if(raiz->esq == NULL && raiz->dir == NULL){

            free(raiz);
            return NULL;
        }

        //caso2: quando o valor da raiz a ser removido possui um filho a direita
        else if(raiz->esq == NULL && raiz->dir != NULL){

            no* retorno = raiz->dir;
            free(raiz);
            return retorno;
        }

        //caso2: quando o valor da raiz a ser removido possui um filho a esquerda
        else if(raiz->esq != NULL && raiz ->dir == NULL){

            no* retorno = raiz->esq;
            free(raiz);
            return retorno;
        }

       //caso3: quando o valor da raiz a ser removido possui 2 filhos
        else{
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

// Função de print da arvore em In-Order
// Em In-Order se pecorre primeiro o lado esquerdo, na volta printa e apos pecorre o lado esquerdo
void inorder(no* raiz){

    // Caso Base, raiz vazia
    if(raiz == NULL){

    }else{

        // Caso recursivo, quando a raiz da arvore esta preenchido

        // Passo 1: Percorrimento do lado esquerdo da arvore
        inorder(raiz->esq);

        // Passo 2: Chamada para imprimir a raiz da arvore, na volta do perccorimento do lado esquerdo
        printf("[%d]", raiz->valor);

        // Passo 3: Percorrimento do lado direito da arvore
        inorder(raiz->dir);
    }
}

// Função que printa a arvore em Pós-Order
// Em Pós-Order se pecorrer todo o lado lado esquerdo e direito, e depois printa
void posorder(no* raiz){

    // Caso Base, raiz vazia
    if(raiz == NULL){

    }else{

        // Caso recursivo, quando a raiz da arvore esta preenchido

        // Passo 1: Percorrimento do lado esquerdo da arvore
        posorder(raiz->esq);

        // Passo 2: Percorrimento do lado direito da arvore
        posorder(raiz->dir);

        // Passo 3: Chamada para imprimir a raiz da arvore
        printf("[%d]", raiz->valor);
    }
}

// Função que imprimi a arvore em modo reverso
// Em reverse se pecorre primeiro o lado direito, printa apos e depois pecorre o esquerdo
void reverse(no* raiz){

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

// Função que conta quantos numeros pares existe na arvore
int qntdPar(no* raiz){

    if(raiz == NULL){
        return 0;
    }
    else{

     if((raiz->valor%2)== 0){
        return 1 + qntdPar(raiz->esq) + qntdPar(raiz->dir);
        }
    else
    {
        return 0 + qntdPar(raiz->esq) + qntdPar(raiz->dir);
    }
    }   
}

// função que eleve os nó da arvore ao quadrado
no* quadrado(no* raiz){

    if(raiz==NULL){

    }else{
    
        raiz->valor = raiz->valor*raiz->valor;
        quadrado(raiz->esq);
        quadrado(raiz->dir);
        return raiz;
    }
}

// função que procura se um numero e existente na arvore
int existe(no* raiz, int valor){

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
