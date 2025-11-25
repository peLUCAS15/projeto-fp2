#ifndef JOGO_H
#define JOGO_H

#include "../include/raylib.h"
#include "palavras.h"

#define maxTentativasFacil 5
#define maxTentativasDificil 3
#define maxTentativas 6
#define maxTamanhoPalavra 10

typedef enum{
    letraNaoUsada = 0,
    letraErrada = 1,
    letraPosicaoErrada = 2,
    letraCorreta = 3
} EstadoLetra;

typedef struct{
    char palavra[maxTamanhoPalavra];
    EstadoLetra estados[maxTamanhoPalavra];
    int tamanho;
} Tentativa;

typedef struct{
    Palavra *palavraAtual;
    Tentativa tentativas[maxTentativas];
    int tentativaAtual;
    char entradaAtual[maxTamanhoPalavra];
    int posEntrada;
    int venceu;
    int perdeu;
    EstadoLetra teclado[26];
    int faseAtual;
    int progressoFases[6];
    int maxTentativasPermitidas;
    float tempoRestante;
    float tempoInicial;
    int tempoEsgotado;
    int dicaRevelada;
    Music somError;
} EstadoJogo;

void inicializarJogo(EstadoJogo *estado, Palavra *palavra, int fase);
int adicionarLetra(EstadoJogo *estado, char letra);
int removerLetra(EstadoJogo *estado);
int fazerTentativa(EstadoJogo *estado);
void atualizarTempo(EstadoJogo *estado, float deltaTime);
void revelarDica(EstadoJogo *estado);
Palavra* selecionarPalavraAleatoria(Palavra *lista, int total, const char *tema);
void salvarProgresso(EstadoJogo *estado);
void carregarProgresso(EstadoJogo *estado);
void resetarProgresso(EstadoJogo *estado);

#endif