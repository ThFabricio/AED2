#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    arvore raiz;
    int opcao, temp;
    raiz = NULL;

    while(1==1) {
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                scanf("%d", &temp);
                raiz = inserir(raiz, temp);
                break;
            
            case 2:
                preorder(raiz);
                printf("\n");
                break;

            case 3:
                inorder(raiz);
                printf("\n");
                break;

            case 4:
                posorder(raiz);
                printf("\n");
                break;

            case 5:

                reverse(raiz);
                printf("\n");
                break;

            case 6:

                qntdPrimos(raiz);
                break;

            case 7:

                scanf("%d", &temp);
                raiz = reajustar(raiz, temp);
                break;

            case 8:

                scanf("%d", &temp);
                printf("%d\n", existe(raiz, temp));
                break;

            case 9:

                scanf("%d", &temp);
                raiz = remover(raiz, temp);
                break;           

            case 99:
                exit(0);
        }
    }
}
