#include <stdio.h>
#include "bst.h"

int main(int argc, char*argv[]) {

    // criação da raiz base da arvore
    no *raiz;

    // inicialização da raiz da arvore   
    raiz = NULL;

    // menu da arvore
    int opcao, valor;

    while (1)
    {
        scanf("%d", &opcao);

        switch (opcao)
        {

            // opção de inserir valores na arvore
            case 1:

                scanf("%d", &valor);
                raiz = inserir(raiz, valor);

                break;

            // opção de imprimir a arvore em Pré-Order
            case 2:

                preorder(raiz);
                printf("\n");
                break;

            // opçao de que calcula a altura da arvore
            case 3:

                printf("%d\n", altura(raiz));

            // opção de remover elemento da arvore
            case 9:

                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                
            // saida do menu
            case 99:

                return 0;
        }
    }

    return (0);  
}