  
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc, char * argv[]) {
	tabela tab;
	int opcao, codigo;
	inicializarTabela(&tab);

	while(1) {
		scanf("%d", &opcao);

		switch(opcao) {
				int valor;
				case 1:
						printf("%d\n", altura(tab.indice));
						break;
				case 2:
						adicionarLivro(&tab, ler_dado());
						break;
				case 3:
						printf("%d\n", maior_elemento(tab.indice)->chave);
						break;
				case 4:
						printf("%d\n", menor_elemento(tab.indice)->chave);
						break;
				case 5:
						pre_order(tab.indice, &tab);
						printf("\n");
						break;
				case 6:
						in_order(tab.indice, &tab);
						printf("\n");
						break;
				case 7:
						pos_order(tab.indice, &tab);
						printf("\n");
						break;
				case 10:
						salvar_arquivo("dados.txt", tab.indice);
						break;
				case 11:
						tab.indice = carregar_arquivo("indice.dat", tab.indice);
						break;
				case 99:
						finalizarTabela(&tab);
						exit(0);
		}
	}
    return 0;
}