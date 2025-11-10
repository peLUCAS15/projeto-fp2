#ifndef CINEMATICA_H
#define CINEMATICA_H

#include "../include/raylib.h"
#include <stdbool.h>

typedef struct{
    Texture2D faseNarutoTerreno;
    Texture2D faseDragonBallTerreno;
    Texture2D faseOnePieceTerreno;
    Texture2D faseHarryPotterTerreno;
    Texture2D faseResidentEvilTerreno;
    Texture2D faseSilentHillTerreno;
    Texture2D faseFinalTerreno;
    Texture2D narutoParado;
    Texture2D narutoAndando;
    Texture2D narutoAndandoL;
    Texture2D narutoCorrendo;
    Texture2D narutoCorrendoL;
    Texture2D narutoPulando;
    Texture2D narutoFalando;
    Texture2D elimurParado;
    Texture2D elimurFalando;
    Texture2D caixaDialogo;
    Texture2D elimurRevelado;
    Texture2D elimurMascara;
    Texture2D elimurTirandoM;
    Texture2D buracoNegro;
    Music musicaFundo;
    Music musicaDeselec;
    Music musicaOnePiece;
    Music musicaNaruto;
    bool carregado;

} RecursosCinematica;

typedef struct{
    int fase;
    int dialogoAtual;
    float narutoX;
    float narutoY;
    bool correndo;
    bool pulando;
    bool cinematicaAtiva;
    bool aguardandoJogo;
    bool inicializado;
} EstadoCinematica;

typedef struct{
    EstadoCinematica estadoIntro;
    EstadoCinematica estadoTransicao;
    float tempoTransicao;
    int Transicao;
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