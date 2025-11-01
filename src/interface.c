#include <stdio.h>
#include <string.h>
#include "interface.h"

void inicializarInterface(EstadoInterface *estadoInterface){
    estadoInterface->texturasCarregadas = false;
    estadoInterface->tecladoInicializado = false;
    
    InitWindow(LARGURA_INICIAL, ALTURA_INICIAL, "Naruto no Multiverso (Wordle)");
    SetTargetFPS(60);
    
    SetExitKey(0);
    
    ClearWindowState(FLAG_WINDOW_RESIZABLE);
    
    if (FileExists("assets/imagens/background.png")){
        estadoInterface->texturaDeFundo = LoadTexture("assets/imagens/background.png");
        estadoInterface->texturasCarregadas = true;
    }
}

void finalizarInterface(void){
    CloseWindow();
}

void desenharBackground(int fase){
    // desenha uma camada semi-transparente
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 80});
    
    // desenha indicador de fase
    const char *temas[] ={"DRAGON BALL", "ONE PIECE", "HARRY POTTER", "RESIDENT EVIL", "SILENT HILL"};
    if (fase >= 1 && fase <= 5){
        DrawText(TextFormat("FASE %d: %s", fase, temas[fase - 1]), 
                 30, 20, 28, YELLOW);
    }
}

void desenharDica(const char *dica){
    // desenha caixa de dica 
    int largura = MeasureText(dica, 20) + 40;
    if (largura > GetScreenWidth() - 100) largura = GetScreenWidth() - 100;
    int x = (GetScreenWidth() - largura) / 2;
    
    DrawRectangle(x, 20, largura, 50, (Color){30, 30, 30, 240});
    DrawRectangleLines(x, 20, largura, 50, YELLOW);
    DrawText("DICA:", x + 10, 25, 18, YELLOW);
    DrawText(dica, x + 10, 45, 16, WHITE);
}

void desenharGrid(EstadoJogo *estado, int x, int y){
    if (estado->palavraAtual == NULL) return;
    
    int tamanhoPalavra = strlen(estado->palavraAtual->palavra);
    int tamanhoCelula = 60;
    int espacamento = 8;
    
    // centraliza o grid horizontalmente e posiciona em cima
    int larguraTotal = tamanhoPalavra * (tamanhoCelula + espacamento);
    x = (GetScreenWidth() - larguraTotal) / 2;
    y = 90; // posição ajustada embaixo da dica 
    
    // usa o número correto de tentativas baseado na fase
    int maxLinhas = estado->maxTentativasPermitidas;
    
    // desenha todas as tentativas
    for (int linha = 0; linha < maxLinhas; linha++){
        for (int col = 0; col < tamanhoPalavra; col++){
            int posX = x + col * (tamanhoCelula + espacamento);
            int posY = y + linha * (tamanhoCelula + espacamento);
            
            Color corFundo = DARKGRAY;
            Color corBorda = LIGHTGRAY;
            char letra = ' ';
            
            // se é uma tentativa já feita
            if (linha < estado->tentativaAtual){
                letra = estado->tentativas[linha].palavra[col];
                
                switch (estado->tentativas[linha].estados[col]){
                    case letraCorreta:
                        corFundo = GREEN;
                        break;
                    case letraPosicaoErrada:
                        corFundo = YELLOW;
                        break;
                    case letraErrada:
                        corFundo = DARKGRAY;
                        break;
                    default:
                        break;
                }
            }
            // se é a tentativa atual
            else if (linha == estado->tentativaAtual && col < estado->posEntrada){
                letra = estado->entradaAtual[col];
                corBorda = WHITE;
            }
            
            // desenha a célula
            DrawRectangle(posX, posY, tamanhoCelula, tamanhoCelula, corFundo);
            DrawRectangleLines(posX, posY, tamanhoCelula, tamanhoCelula, corBorda);
            
            // desenha a letra
            if (letra != ' '){
                char texto[2] ={letra, '\0'};
                int larguraTexto = MeasureText(texto, 45);
                DrawText(texto, 
                        posX + (tamanhoCelula - larguraTexto) / 2, 
                        posY + 18, 
                        45, 
                        WHITE);
            }
        }
    }
}

void inicializarTeclado(TecladoVirtual *teclado){
    const char *linhas[] ={"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};
    int larguraTecla = 60; 
    int alturaTecla = 60;   
    int espacamento = 5;     
    int yBase = GetScreenHeight() - 280; 
    
    int idx = 0;
    for (int linha = 0; linha < 3; linha++){
        int numTeclas = strlen(linhas[linha]);
        int larguraTotalLinha = numTeclas * larguraTecla + (numTeclas - 1) * espacamento;
        int xInicial = (GetScreenWidth() - larguraTotalLinha) / 2;
        
        // linhas centralizadas
        
        for (int i = 0; i < numTeclas; i++){
            teclado->letras[idx] = linhas[linha][i];
            teclado->teclas[idx] = (Rectangle){
                xInicial + i * (larguraTecla + espacamento),
                yBase + linha * (alturaTecla + espacamento),
                larguraTecla,
                alturaTecla
            };
            idx++;
        }
    }
}

void desenharTeclado(EstadoJogo *estado, TecladoVirtual *teclado){
    for (int i = 0; i < 26; i++){
        Rectangle rect = teclado->teclas[i];
        char letra = teclado->letras[i];
        
        // determina a cor baseada no estado da letra
        Color corFundo = LIGHTGRAY;
        int indice = letra - 'A';
        
        if (indice >= 0 && indice < 26){
            switch (estado->teclado[indice]){
                case letraCorreta:
                    corFundo = GREEN;
                    break;
                case letraPosicaoErrada:
                    corFundo = YELLOW;
                    break;
                case letraErrada:
                    corFundo = DARKGRAY;
                    break;
                default:
                    corFundo = LIGHTGRAY;
                    break;
            }
        }
        
        // desenha a tecla
        DrawRectangleRounded(rect, 0.2f, 10, corFundo);
        
        Vector2 posicaoMouse = GetMousePosition();
        if (CheckCollisionPointRec(posicaoMouse, rect)){
            DrawRectangleRoundedLines(rect, 0.2f, 10, WHITE);
        }
        
        // desenha a letra 
        char texto[2] ={letra, '\0'};
        int fonte = 28;  // fonte maior para melhor legibilidade
        int largura = MeasureText(texto, fonte);
        DrawText(texto, 
                rect.x + (rect.width - largura) / 2, 
                rect.y + (rect.height - fonte) / 2 + 2,  // centralizado verticalmente
                fonte, 
                WHITE);
    }
    
    // desenha teclas especiais (enter delete) abaixo do teclado
    int yEspeciais = GetScreenHeight() - 85; 
    int larguraBotao = 160;
    int alturaBotao = 50;
    int espacamentoBotoes = 5; 
    
    int larguraTotalBotoes = larguraBotao * 2 + espacamentoBotoes;
    int xInicialBotoes = (GetScreenWidth() - larguraTotalBotoes) / 2;
    
    Vector2 posicaoMouse = GetMousePosition();
    
    Rectangle enterRect ={xInicialBotoes, yEspeciais, larguraBotao, alturaBotao};
    DrawRectangleRounded(enterRect, 0.2f, 10, LIGHTGRAY);
    
    if (CheckCollisionPointRec(posicaoMouse, enterRect)){
        DrawRectangleRoundedLines(enterRect, 0.2f, 10, WHITE);
    }
    
    int larguraEnter = MeasureText("ENTER", 20);
    DrawText("ENTER", enterRect.x + (larguraBotao - larguraEnter) / 2, enterRect.y + 16, 20, WHITE);
    
    Rectangle backRect ={xInicialBotoes + larguraBotao + espacamentoBotoes, yEspeciais, larguraBotao, alturaBotao};
    DrawRectangleRounded(backRect, 0.2f, 10, LIGHTGRAY);
    
    if (CheckCollisionPointRec(posicaoMouse, backRect)){
        DrawRectangleRoundedLines(backRect, 0.2f, 10, WHITE);
    }
    
    int larguraDelete = MeasureText("DELETE", 20);
    DrawText("DELETE", backRect.x + (larguraBotao - larguraDelete) / 2, backRect.y + 16, 20, WHITE);
}

char verificarCliqueTeclado(TecladoVirtual *teclado, Vector2 posicaoMouse){
    for (int i = 0; i < 26; i++){
        if (CheckCollisionPointRec(posicaoMouse, teclado->teclas[i])){
            return teclado->letras[i];
        }
    }
    
    // verifica o enter e o delete (ajustadas com as mesmas dimensões do desenho)
    int yEspeciais = GetScreenHeight() - 85;
    int larguraBotao = 160;
    int alturaBotao = 50;
    int espacamentoBotoes = 5;  
    int larguraTotalBotoes = larguraBotao * 2 + espacamentoBotoes;
    int xInicialBotoes = (GetScreenWidth() - larguraTotalBotoes) / 2;
    
    Rectangle enterRect ={xInicialBotoes, yEspeciais, larguraBotao, alturaBotao};
    Rectangle backRect ={xInicialBotoes + larguraBotao + espacamentoBotoes, yEspeciais, larguraBotao, alturaBotao};
    
    if (CheckCollisionPointRec(posicaoMouse, enterRect)){
        return '\n'; // enter
    }
    if (CheckCollisionPointRec(posicaoMouse, backRect)){
        return '\b'; // espaco
    }
    
    return '\0';
}

void desenharMensagemFinal(EstadoJogo *estado){
    if (!estado->venceu && !estado->perdeu) return;
    
    // camada overlay escura
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 180});
    
    // caixa de mensagem
    int larguraCaixa = 500;
    int alturaCaixa = 250;
    int x = (GetScreenWidth() - larguraCaixa) / 2;
    int y = (GetScreenHeight() - alturaCaixa) / 2;
    
    DrawRectangle(x, y, larguraCaixa, alturaCaixa, (Color){30, 30, 30, 255});
    DrawRectangleLines(x, y, larguraCaixa, alturaCaixa, YELLOW);
    
    if (estado->venceu){
        // centraliza cada texto
        int larguraParabens = MeasureText("PARABÉNS!", 42);
        DrawText("PARABÉNS!", x + (larguraCaixa - larguraParabens) / 2, y + 40, 42, GREEN);
        
        int larguraAcertou = MeasureText("Você acertou a palavra!", 26);
        DrawText("Você acertou a palavra!", x + (larguraCaixa - larguraAcertou) / 2, y + 100, 26, WHITE);
        
        int larguraPalavra = MeasureText(estado->palavraAtual->palavra, 34);
        DrawText(estado->palavraAtual->palavra, x + (larguraCaixa - larguraPalavra) / 2, y + 140, 34, YELLOW);
        
        int larguraContinuar = MeasureText("Pressione ESPAÇO para continuar", 18);
        DrawText("Pressione ESPAÇO para continuar", x + (larguraCaixa - larguraContinuar) / 2, y + 200, 18, LIGHTGRAY);
    } else if (estado->perdeu){
        int larguraPena = MeasureText("QUE PENA!", 42);
        DrawText("QUE PENA!", x + (larguraCaixa - larguraPena) / 2, y + 40, 42, RED);
        
        int larguraEra = MeasureText("A palavra era:", 26);
        DrawText("A palavra era:", x + (larguraCaixa - larguraEra) / 2, y + 100, 26, WHITE);
        
        int larguraPalavra = MeasureText(estado->palavraAtual->palavra, 34);
        DrawText(estado->palavraAtual->palavra, x + (larguraCaixa - larguraPalavra) / 2, y + 140, 34, YELLOW);
        
        int larguraTentar = MeasureText("Pressione ESPAÇO para tentar novamente", 18);
        DrawText("Pressione ESPAÇO para tentar novamente", x + (larguraCaixa - larguraTentar) / 2, y + 200, 18, LIGHTGRAY);
    }
}

int desenharMenuFases(EstadoJogo *estado, Texture2D imagemFundo){
    if (imagemFundo.id > 0){
        DrawTexturePro(
            imagemFundo,
            (Rectangle){0, 0, (float)imagemFundo.width, (float)imagemFundo.height},
            (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
    } else{
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){20, 20, 40, 255});
    }
    
    const char *titulo = "SELECIONE UMA FASE";
    int larguraTitulo = MeasureText(titulo, 46);
    DrawText(titulo, (GetScreenWidth() - larguraTitulo) / 2, 70, 46, YELLOW);
    
    const char *nomesFases[] ={
        "FASE 1 : DRAGON BALL",
        "FASE 2 : ONE PIECE",
        "FASE 3 : HARRY POTTER",
        "FASE 4 : RESIDENT EVIL",
        "FASE 5 : SILENT HILL"
    };
    
    int faseSelecionada = -1;
    Vector2 posicaoMouse = GetMousePosition();
    bool clicou = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    
    for (int i = 0; i < 5; i++){
        int y = 200 + i * 95;
        Rectangle botao ={GetScreenWidth() / 2 - 300, y, 600, 75};
        
        Color cor = DARKGRAY;
        
        bool bloqueada = (estado->progressoFases[i] == 0);
        bool concluida = (estado->progressoFases[i] == 2);
        
        if (bloqueada){
            cor = (Color){50, 50, 50, 255};
        } else if (concluida){
            cor = GREEN;
        } else if (CheckCollisionPointRec(posicaoMouse, botao)){
            cor = YELLOW;
            if (clicou){
                faseSelecionada = i + 1;
            }
        }
        
        DrawRectangleRounded(botao, 0.1f, 10, cor);
        DrawRectangleRoundedLines(botao, 0.1f, 10, WHITE);
        
        const char *texto = nomesFases[i];
        if (bloqueada){
            DrawText("BLOQUEADA", botao.x + 240, botao.y + 25, 26, LIGHTGRAY);
        } else if (concluida){
            DrawText(texto, botao.x + 140, botao.y + 25, 26, WHITE);
        } else{
            DrawText(texto, botao.x + 140, botao.y + 25, 26, WHITE);
        }
    }
    
    // botão de resetar progresso
    int yResetar = 200 + 5 * 95 + 20;
    Rectangle botaoResetar ={GetScreenWidth() / 2 - 200, yResetar, 400, 60};
    
    Color corResetar = (Color){150, 50, 50, 255};
    if (CheckCollisionPointRec(posicaoMouse, botaoResetar)){
        corResetar = RED;
        if (clicou){
            faseSelecionada = -2; // código para resetar
        }
    }
    
    DrawRectangleRounded(botaoResetar, 0.1f, 10, corResetar);
    DrawRectangleRoundedLines(botaoResetar, 0.1f, 10, WHITE);
    
    const char *textoResetar = "RESETAR PROGRESSO";
    int larguraResetar = MeasureText(textoResetar, 24);
    DrawText(textoResetar, (GetScreenWidth() - larguraResetar) / 2, yResetar + 18, 24, WHITE);
    
    const char *textoESC = "ESC - Para voltar ao menu inicial";
    int larguraTextoESC = MeasureText(textoESC, 18);
    DrawText(textoESC, (GetScreenWidth() - larguraTextoESC) / 2, GetScreenHeight() - 30, 18, GRAY);
    
    return faseSelecionada;
}

void desenharJogo(EstadoJogo *estado, Texture2D terrenoFase, EstadoInterface *estadoInterface){
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (terrenoFase.id > 0){
        DrawTexturePro(terrenoFase, 
                      (Rectangle){0, 0, (float)terrenoFase.width, (float)terrenoFase.height},
                      (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                      (Vector2){0, 0}, 0.0f, WHITE);
    }
    
    desenharBackground(estado->faseAtual);
    
    desenharDica(estado->palavraAtual->dica);
    desenharGrid(estado, 100, 200);
    
    if (!estadoInterface->tecladoInicializado){
        inicializarTeclado(&estadoInterface->teclado);
        estadoInterface->tecladoInicializado = true;
    }
    
    desenharTeclado(estado, &estadoInterface->teclado);
    desenharMensagemFinal(estado);
    
    EndDrawing();
}
