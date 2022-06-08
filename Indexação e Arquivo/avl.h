#ifndef AVL_H
#define AVL_H

typedef struct livro{

	int codigo;
	char *titulo;
	char *autor;
	char *ano;
}dado;

typedef struct indice{

	int chave;
	int indice;
}tipo_dado;

// typedef int tipo_dado;

typedef struct no_avl {
	tipo_dado *dado;
	int fb;
	struct no_avl *esq, *dir;
} no_avl;

typedef no_avl * arvore;

typedef struct tabela{

	FILE *arquivo_dados;
	arvore indice;
}tabela;


void inicializar(arvore *raiz);
arvore adicionar (tipo_dado *valor, arvore raiz, int *cresceu);
arvore remover (int valor, arvore raiz, int *diminuiu);

int maior(int a, int b);
int altura(arvore raiz);
tipo_dado *  maior_elemento(arvore raiz);
tipo_dado *  menor_elemento(arvore raiz);
void pre_order(arvore raiz, tabela *tab);
void pos_order(arvore raiz, tabela *tab);
void in_order(arvore raiz, tabela *tab);

void imprimir_elemento(arvore raiz, tabela *tab);

arvore rotacionar(arvore raiz);
arvore rotacao_simples_direita(arvore raiz);
arvore rotacao_simples_esquerda(arvore raiz);
arvore rotacao_dupla_direita(arvore raiz);
arvore rotacao_dupla_esquerda(arvore raiz);
tipo_dado * maior_elemento_esquerda(arvore raiz);

int inicializarTabela (tabela *tab);
void finalizarTabela (tabela *tab);

void salvar_arquivo(char *nome, arvore a);
void salvar_auxiliar(arvore raiz, FILE *arq);
arvore carregar_arquivo(char *nome, arvore a);
dado *ler_dado();
void tirar_enter();

void adicionarLivro(tabela *tab, dado *livro);
void buscar_livro(int condigo, arvore raiz, tabela *tab);


#endif
