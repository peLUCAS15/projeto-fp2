#ifndef CINEMATICA_H
#define CINEMATICA_H

#include "../include/raylib.h"
#include <stdbool.h>

typedef struct{
    int monitor;
    Texture2D fases[15];
    Texture2D sprites[12];
    Music trilhaSonora[7];
    Texture2D elimurRevelado;
    Texture2D elimurMascara;
    Texture2D elimurTirandoM;
    bool carregado;
} RecursosCinematica;

typedef struct{
    int fase;
    int dialogoAtual;
    float narutoX;
    float narutoY;
    bool correndo;
    bool cinematicaAtiva;
    bool aguardandoJogo;
    bool inicializado;
} EstadoCinematica;

typedef struct{
    bool pulando;
    EstadoCinematica estadoIntro;
    EstadoCinematica estadoTransicao;
    float tempoFinal;
    float tempoAnimacao;
    float tempoPulo;
    int pulo;
    int animacao;
    int final;
    float narutoXTransicao;
    bool inicializadoTransicao;
} EstadoCinematicas;

bool carregarRecursosCinematica(RecursosCinematica *recursos);
void descarregarRecursosCinematica(RecursosCinematica *recursos);
void inicializarCinematica(EstadoCinematica *estado, int fase);
bool atualizarCinematica(EstadoCinematica *estado);
void desenharCinematica(EstadoCinematica *estado, RecursosCinematica *recursos);
bool executarCinematicaIntro(RecursosCinematica *recursos, int fase, EstadoCinematicas *estados);
bool executarCinematicaTransicao(RecursosCinematica *recursos, int fase, EstadoCinematicas *estados);

#endif