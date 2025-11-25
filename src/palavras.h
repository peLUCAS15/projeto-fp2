#ifndef PALAVRAS_H
#define PALAVRAS_H

typedef struct{
    char palavra[30];
    char dica[100];
    int dificuldade;
    char tema[30];
} Palavra;

void adicionarPalavraDireta(Palavra **lista, int *total, char *palavra, char *dica, int dificuldade, char *tema);
void carregarPalavrasIniciais(Palavra **lista, int *total);
int carregarPalavrasCSV(Palavra **lista, int *total, const char *nomeArquivo);
void liberarPalavras(Palavra *lista);

// Funções para gerenciamento de palavras
int salvarPalavrasCSV(Palavra *lista, int total, const char *nomeArquivo);
int buscarPalavra(Palavra *lista, int total, const char *palavra);
void removerPalavra(Palavra **lista, int *total, int indice);
void alterarPalavra(Palavra *lista, int total, int indice, char *novaPalavra, char *novaDica, int novaDificuldade, char *novoTema);
void listarPalavrasPorTema(Palavra *lista, int total, const char *tema);
void listarTodasPalavras(Palavra *lista, int total);

#endif