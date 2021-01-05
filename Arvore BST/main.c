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

            // opçao de imprimir a arvore em In-Order
            case 3:

                inorder(raiz);
                printf("\n");
                break;

            // opção de imprimir a arvore em Pós-Order
            case 4:

                posorder(raiz);
                printf("\n");
                break;

            // opção de imprimir a arvore de forma reversa
            case 5:

                reverse(raiz);
                printf("\n");
                break;

            // opção que conta a quantidade de numeros pares da arvore
            case 6:

                printf("%d\n", qntdPar(raiz));
                break;

            // função que trasforma o nó de uma arvore em quadrado
            case 7:

                quadrado(raiz);
                break;

            case 8:

                scanf("%d", &valor);
                printf("%d", existe(raiz, valor));
                break;

            // opção de remover elemento da arvore
            case 9:

                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;
                
            // saida do menu
            case 99:

                return 0;
        }
    }

    return (0);  
}