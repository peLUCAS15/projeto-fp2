#ifndef PERGUNTA_H
#define PERGUNTA_H

typedef struct {
    int id;
    char texto[256];
    char resposta[256];
} Pergunta;

void criarPergunta(Pergunta *p);

#endif