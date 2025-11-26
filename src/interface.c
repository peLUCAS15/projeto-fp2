/**
 * Lugar responsavel por criar a interface do jogo
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "interface.h"

void inicializarInterface(EstadoInterface *estadoInterface){
    estadoInterface->texturasCarregadas = false;
    estadoInterface->tecladoInicializado = false;
    //ivita o desperdiçar memória

    InitWindow(LARGURA_INICIAL, ALTURA_INICIAL, "Naruto no Multiverso (Wordle)");//definindo o tamanho da janela
    SetTargetFPS(60);//definindo a quantidade de frames
    
    SetExitKey(0);//definindo que nenhuma tecla fecha a janela
    
    ClearWindowState(FLAG_WINDOW_RESIZABLE);//nao permite arrastar a tela
    
    if (FileExists("assets/imagens/background.png")){
        estadoInterface->texturaDeFundo = LoadTexture("assets/imagens/background.png");
        estadoInterface->texturasCarregadas = true;//carregando a imagem
    }//if
}//inicializarInterface

void finalizarInterface(void){
    CloseWindow();//fecha a janela
}//finalizarInterface

void desenharBackground(int fase){
    // desenha uma camada semi-transparente
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 80});
    
    // desenha indicador de fase
    const char *temas[] ={"NARUTO", "DRAGON BALL", "ONE PIECE", "HARRY POTTER", "RESIDENT EVIL", "SILENT HILL", "FINAL"};
    if (fase >= 1 && fase <= 7){
        DrawText(TextFormat("FASE %d: %s", fase - 1, temas[fase - 1]), 
                 30, 20, 28, YELLOW);
    }//if
}//desenharBackground

void desenharDica(EstadoJogo *estado){
    if (estado == NULL || estado->palavraAtual == NULL) return;//caso nao ache nenhuma palavra, ele para aqui
    
    const char *dica = estado->palavraAtual->dica;
    int x = (GetScreenWidth() - 400) / 2;
    

    // verifica se a dica esta revelada ou nao
    if (estado->dicaRevelada){
        int largura = MeasureText(dica, 20) + 40;
        if (largura > GetScreenWidth() - 100) largura = GetScreenWidth() - 100;
        x = (GetScreenWidth() - largura) / 2;
        
        //desenha a area da dica
        DrawRectangle(x, 20, largura, 50, (Color){30, 30, 30, 240});
        DrawRectangleLines(x, 20, largura, 50, YELLOW);
        DrawText("DICA:", x + 10, 25, 18, YELLOW);
        DrawText(dica, x + 10, 45, 16, WHITE);
    } else{
        // desenha botão para revelar dica
        int largura = 400;
        x = (GetScreenWidth() - largura) / 2;
        
        Rectangle botaoDica = {x, 20, largura, 50};
        Vector2 posicaoMouse = GetMousePosition();
        bool hover = CheckCollisionPointRec(posicaoMouse, botaoDica);
        
        // a cor muda conforme o mouse esta sobre a dica
        Color corFundo = hover ? (Color){50, 50, 50, 240} : (Color){30, 30, 30, 240};// if/else compacto
        Color corBorda = hover ? WHITE : YELLOW; //if/else compacto
        
        DrawRectangle(botaoDica.x, botaoDica.y, botaoDica.width, botaoDica.height, corFundo);
        DrawRectangleLines(botaoDica.x, botaoDica.y, botaoDica.width, botaoDica.height, corBorda);
        
        const char *texto = "CLIQUE PARA REVELAR DICA (-20s)";
        int larguraTexto = MeasureText(texto, 18);
        DrawText(texto, x + (largura - larguraTexto) / 2, 35, 18, YELLOW);//desenha o texto
        
        // verifica clique
        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            revelarDica(estado);
        }//if
    }//else
}//desenharDica

void desenharCronometro(EstadoJogo *estado){
    if (estado == NULL) return;
    
    int minutos = (int)(estado->tempoRestante) / 60;
    int segundos = (int)(estado->tempoRestante) % 60;
    
    // define a cor baseada no tempo restante
    Color corTempo;
    if (estado->tempoRestante <= 10.0f){
        // vermelho piscando quando <= 10 segundos
        float blink = (sinf(GetTime() * 8.0f) + 1.0f) / 2.0f;
        corTempo = (Color){255, (unsigned char)(50 * blink), (unsigned char)(50 * blink), 255};
    } else if (estado->tempoRestante <= 30.0f){
        corTempo = ORANGE; // laranja quando <= 30 segundos
    } else{
        corTempo = YELLOW; // amarelo quando tem bastante tempo
    }
    
    // formata o texto do cronômetro
    const char *textoTempo = TextFormat("%02d:%02d", minutos, segundos);
    
    // posiciona no canto superior direito
    int tamanhoFonte = 50;
    int larguraTexto = MeasureText(textoTempo, tamanhoFonte);
    int x = GetScreenWidth() - larguraTexto - 40;
    int y = 20;
    
    // desenha o tempo (apenas o texto, sem bordas ou fundo)
    DrawText(textoTempo, x, y, tamanhoFonte, corTempo);
    
    // desenha mensagem se o tempo acabou
    if (estado->tempoEsgotado){
        int larguraMensagem = MeasureText("TEMPO ESGOTADO!", 60);
        int xMensagem = (GetScreenWidth() - larguraMensagem) / 2;
        DrawText("TEMPO ESGOTADO!", xMensagem, GetScreenHeight() / 2 - 100, 60, RED);
    }
}

void desenharGrid(EstadoJogo *estado, int x, int y){
    if (estado->palavraAtual == NULL) return;
    
    int tamanhoPalavra = (int)strlen(estado->palavraAtual->palavra);
    int tamanhoCelula = 60;
    int espacamento = 8;
    
    // centraliza o grid horizontalmente e posiciona em cima
    int larguraTotal = tamanhoPalavra * tamanhoCelula + (tamanhoPalavra - 1) * espacamento;
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
                }//switch
            }//if

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
    const char *linhas[] ={"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};//letras do teclado
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
            };//definindo o tamanho de cada tecla
            idx++;
        }//for
    }//for
}//inicializarTeclado

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
            }//switch
        }//if
        
        // desenha a tecla
        DrawRectangleRounded(rect, 0.2f, 10, corFundo);
        
        Vector2 posicaoMouse = GetMousePosition();
        if (CheckCollisionPointRec(posicaoMouse, rect)){
            DrawRectangleRoundedLines(rect, 0.2f, 10, WHITE);
        }//if
        
        // desenha a letra 
        char texto[2] ={letra, '\0'};
        int fonte = 28;  // fonte maior para melhor legibilidade
        int largura = MeasureText(texto, fonte);
        DrawText(texto, 
                rect.x + (rect.width - largura) / 2, 
                rect.y + (rect.height - fonte) / 2 + 2,  // centralizado verticalmente
                fonte, 
                WHITE);
    }//for
    
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
    }//if
    
    int larguraEnter = MeasureText("ENTER", 20);
    DrawText("ENTER", enterRect.x + (larguraBotao - larguraEnter) / 2, enterRect.y + 16, 20, WHITE);
    
    Rectangle backRect ={xInicialBotoes + larguraBotao + espacamentoBotoes, yEspeciais, larguraBotao, alturaBotao};
    DrawRectangleRounded(backRect, 0.2f, 10, LIGHTGRAY);
    
    if (CheckCollisionPointRec(posicaoMouse, backRect)){
        DrawRectangleRoundedLines(backRect, 0.2f, 10, WHITE);
    }//if
    
    int larguraDelete = MeasureText("DELETE", 20);
    DrawText("DELETE", backRect.x + (larguraBotao - larguraDelete) / 2, backRect.y + 16, 20, WHITE);
}

char verificarCliqueTeclado(TecladoVirtual *teclado, Vector2 posicaoMouse){
    for (int i = 0; i < 26; i++){
        if (CheckCollisionPointRec(posicaoMouse, teclado->teclas[i])){
            return teclado->letras[i];
        }//if
    }//for
    
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
    }//if
    if (CheckCollisionPointRec(posicaoMouse, backRect)){
        return '\b'; // espaco
    }//if
    
    return '\0';
}//verificarCliqueTeclado

void desenharMensagemFinal(EstadoJogo *estado){
    if (estado == NULL || estado->palavraAtual == NULL) return;
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
    
    //se o usuario venceu
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
    }//else
}//desenharMensagemFinal

int desenharMenuFases(EstadoJogo *estado, Texture2D imagemFundo){
    if (imagemFundo.id > 0){
        DrawTexturePro(
            imagemFundo,
            (Rectangle){0, 0, (float)imagemFundo.width, (float)imagemFundo.height},
            (Rectangle){0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );//redimencionando imagem de fundo
    } else{
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){20, 20, 40, 255});
    }//else
    
    const char *titulo = "SELECIONE UMA FASE";
    int larguraTitulo = MeasureText(titulo, 46);
    DrawText(titulo, (GetScreenWidth() - larguraTitulo) / 2, 45, 46, YELLOW);
    
    const char *nomesFases[] ={
        "FASE 0 : NARUTO",
        "FASE 1 : DRAGON BALL",
        "FASE 2 : ONE PIECE",
        "FASE 3 : HARRY POTTER",
        "FASE 4 : RESIDENT EVIL",
        "FASE 5 : SILENT HILL",
        "FASE 6 : FINAL"
    };//fases
    
    int faseSelecionada = -1;
    Vector2 posicaoMouse = GetMousePosition();
    bool clicou = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    
    //botoes das fases
    for (int i = 0; i < 7; i++){
        int y = 120 + i * 80;
        Rectangle botao ={GetScreenWidth() / 2 - 300, y, 600, 70};
        
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
            }//if
        }//else
        
        DrawRectangleRounded(botao, 0.1f, 10, cor);
        DrawRectangleRoundedLines(botao, 0.1f, 10, WHITE);
        
        const char *texto = nomesFases[i];
        if (bloqueada){
            DrawText("BLOQUEADA", botao.x + 240, botao.y + 25, 26, LIGHTGRAY);
        } else if (concluida){
            DrawText(texto, botao.x + 140, botao.y + 25, 26, WHITE);
        } else{
            DrawText(texto, botao.x + 140, botao.y + 25, 26, WHITE);
        }//else
    }//for
    
    // botão de resetar progresso
    int yResetar = 120 + 7 * 80;
    Rectangle botaoResetar ={GetScreenWidth() / 2 - 200, yResetar, 400, 50};
    
    Color corResetar = (Color){150, 50, 50, 255};
    if (CheckCollisionPointRec(posicaoMouse, botaoResetar)){
        corResetar = RED;
        if (clicou){
            faseSelecionada = -2; // código para resetar
        }//if
    }//if
    
    DrawRectangleRounded(botaoResetar, 0.1f, 10, corResetar);
    DrawRectangleRoundedLines(botaoResetar, 0.1f, 10, WHITE);
    
    const char *textoResetar = "RESETAR PROGRESSO";
    int larguraResetar = MeasureText(textoResetar, 24);
    DrawText(textoResetar, (GetScreenWidth() - larguraResetar) / 2, yResetar + 13, 24, WHITE);
    
    const char *textoESC = "ESC - Para voltar ao menu inicial";
    int larguraTextoESC = MeasureText(textoESC, 18);
    DrawText(textoESC, (GetScreenWidth() - larguraTextoESC) / 2, yResetar + 65, 18, GRAY);
    
    return faseSelecionada;
}//desenharMenuFases

void desenharJogo(EstadoJogo *estado, Texture2D terrenoFase, EstadoInterface *estadoInterface){
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (terrenoFase.id > 0){
        DrawTexturePro(terrenoFase, //redimensionando a imagem
                      (Rectangle){0, 0, (float)terrenoFase.width, (float)terrenoFase.height},
                      (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                      (Vector2){0, 0}, 0.0f, WHITE);
    }//if
    
    desenharBackground(estado->faseAtual);
    
    if (estado != NULL && estado->palavraAtual != NULL){
        desenharDica(estado);//chamando funçao
        desenharCronometro(estado);//chamando funçao
    }//if
    desenharGrid(estado, 100, 200);
    
    if (!estadoInterface->tecladoInicializado){
        inicializarTeclado(&estadoInterface->teclado);//chamando funçao
        estadoInterface->tecladoInicializado = true;
    }//if
    
    desenharTeclado(estado, &estadoInterface->teclado);//chamando funçao
    desenharMensagemFinal(estado);//chamando funçao
    
    EndDrawing();
}//desenharJogo