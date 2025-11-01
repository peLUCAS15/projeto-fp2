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

#endif
