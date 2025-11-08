#ifndef INTERFACE_H
#define INTERFACE_H

#include "../include/raylib.h"
#include "jogo.h" 

// dimensao inicial da janela
#define LARGURA_INICIAL 1200
#define ALTURA_INICIAL 800

typedef struct{
    Rectangle teclas[26];
    char letras[26];
} TecladoVirtual;

typedef struct{
    Texture2D texturaDeFundo;
    bool texturasCarregadas;
    TecladoVirtual teclado;
    bool tecladoInicializado;
} EstadoInterface;

void inicializarInterface(EstadoInterface *estadoInterface);
void finalizarInterface(void);
void desenharJogo(EstadoJogo *estado, Texture2D terrenoFase, EstadoInterface *estadoInterface);
void desenharGrid(EstadoJogo *estado, int x, int y);
void desenharTeclado(EstadoJogo *estado, TecladoVirtual *teclado);
void inicializarTeclado(TecladoVirtual *teclado);
char verificarCliqueTeclado(TecladoVirtual *teclado, Vector2 posicaoMouse);
void desenharBackground(int fase);
void desenharDica(const char *dica);
void desenharMensagemFinal(EstadoJogo *estado);
int desenharMenuFases(EstadoJogo *estado, Texture2D imagemFundo);

#endif
