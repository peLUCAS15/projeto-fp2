#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "palavras.h"
#include "jogo.h"
#include "interface.h"
#include "cinematica.h"

typedef enum{
    TELA_MENU_INICIAL,
    TELA_INSTRUCOES,
    TELA_CREDITOS,
    TELA_PALAVRAS,
    TELA_MENU,
    TELA_CINEMATICA,
    TELA_JOGO,
    TELA_RESULTADO,
    TELA_TRANSICAO,
    TELA_PARABENS,
    TELA_SAIR
} EstadoTela;

const char *temasFases[] ={
    "Naruto",
    "Dragon Ball",
    "One Piece",
    "Harry Potter",
    "Resident Evil",
    "Silent Hill",
    "Final",
    "Epilogo"
};


int processarEntrada(EstadoJogo *estado, TecladoVirtual *teclado){
    int atualizar = 0;
    
    // verifica teclado físico
    int tecla = GetKeyPressed();
    if (tecla >= KEY_A && tecla <= KEY_Z){
        char letra = 'A' + (tecla - KEY_A);
        if (adicionarLetra(estado, letra)){
            atualizar = 1;
        }
    } else if (tecla == KEY_BACKSPACE){
        if (removerLetra(estado)){
            atualizar = 1;
        }
    } else if (tecla == KEY_ENTER){
        if (fazerTentativa(estado)){
            atualizar = 1;
        }
    }
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 posicaoMouse = GetMousePosition();
        char letra = verificarCliqueTeclado(teclado, posicaoMouse);
        
        if (letra >= 'A' && letra <= 'Z'){
            if (adicionarLetra(estado, letra)){
                atualizar = 1;
            }
        } else if (letra == '\n'){ // enter
            if (fazerTentativa(estado)){
                atualizar = 1;
            }
        } else if (letra == '\b'){ // espaco
            if (removerLetra(estado)){
                atualizar = 1;
            }
        }
    }
    
    return atualizar;
}

void desenharMenuInicial(Texture2D imagemMenu, int *opcaoSelecionada){
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (imagemMenu.id > 0){
        DrawTexturePro(
            imagemMenu,
            (Rectangle){0, 0, (float)imagemMenu.width, (float)imagemMenu.height},
            (Rectangle){0, 0, 1200, 800},
            (Vector2){0, 0},
            0.0f,
            WHITE
        );
    }
    
    const char *titulo = "NARUTO NO MULTIVERSO";
    int larguraTitulo = MeasureText(titulo, 60);
    DrawText(titulo, (1200 - larguraTitulo) / 2, 120, 60, ORANGE);
    
    const char *subtitulo = "Wordle Edition";
    int larguraSubtitulo = MeasureText(subtitulo, 30);
    DrawText(subtitulo, (1200 - larguraSubtitulo) / 2, 190, 30, YELLOW);
    
    Vector2 posicaoMouse = GetMousePosition();
    
    const char *opcoes[] ={"INICIAR", "PALAVRAS", "INSTRUCOES", "CREDITOS", "SAIR"};
    int yInicial = 320;
    int espacamento = 90;
    int larguraBotao = 350;
    int alturaBotao = 65;
    
    for (int i = 0; i < 5; i++){
        int y = yInicial + (i * espacamento);
        Rectangle botao ={(1200 - larguraBotao) / 2, (float)y, (float)larguraBotao, (float)alturaBotao};
        
        Color cor = WHITE;
        Color corFundo = (Color){30, 30, 30, 220};
        if (CheckCollisionPointRec(posicaoMouse, botao)){
            cor = ORANGE;
            corFundo = (Color){60, 60, 60, 240};
            *opcaoSelecionada = i;
        }
        
        DrawRectangleRec(botao, corFundo);
        DrawRectangleLinesEx(botao, 3, cor);
        int larguraTexto = MeasureText(opcoes[i], 35);
        DrawText(opcoes[i], (1200 - larguraTexto) / 2, y + 17, 35, cor);
    }
    
    EndDrawing();
}

void desenharInstrucoes(Texture2D imagemMenu){
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (imagemMenu.id > 0){
        DrawTexturePro(
            imagemMenu,
            (Rectangle){0, 0, (float)imagemMenu.width, (float)imagemMenu.height},
            (Rectangle){0, 0, 1200, 800},
            (Vector2){0, 0},
            0.0f,
            (Color){255, 255, 255, 100}
        );
    }
    
    DrawRectangle(0, 0, 1200, 800, (Color){0, 0, 0, 200});
    
    DrawText("INSTRUCOES", 400, 50, 40, ORANGE);
    
    DrawText("COMO JOGAR:", 100, 150, 25, YELLOW);
    DrawText("- Adivinhe a palavra secreta em ate 5 tentativas (fases 1-2) ou 3 (fases 3-5)", 120, 190, 20, WHITE);
    DrawText("- Cada tentativa deve ser uma palavra valida", 120, 220, 20, WHITE);
    DrawText("- Use o teclado virtual ou fisico para digitar", 120, 250, 20, WHITE);
    
    DrawText("CORES:", 100, 310, 25, YELLOW);
    DrawText("- Verde: Letra correta na posicao correta", 120, 350, 20, GREEN);
    DrawText("- Amarelo: Letra existe mas na posicao errada", 120, 380, 20, YELLOW);
    DrawText("- Cinza: Letra nao existe na palavra", 120, 410, 20, GRAY);
    
    DrawText("FASES:", 100, 470, 25, YELLOW);
    DrawText("- Complete cada fase para desbloquear a proxima", 120, 510, 20, WHITE);
    DrawText("- Cada fase tem um tema diferente: Dragon Ball, One Piece, etc.", 120, 540, 20, WHITE);
    
    DrawText("Pressione ESC ou clique para voltar", 350, 720, 25, ORANGE);
    
    EndDrawing();
}

void desenharCreditos(Texture2D imagemMenu){
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (imagemMenu.id > 0){
        DrawTexturePro(
            imagemMenu,
            (Rectangle){0, 0, (float)imagemMenu.width, (float)imagemMenu.height},
            (Rectangle){0, 0, 1200, 800},
            (Vector2){0, 0},
            0.0f,
            (Color){255, 255, 255, 100}
        );
    }
    
    DrawRectangle(0, 0, 1200, 800, (Color){0, 0, 0, 200});
    
    DrawText("CREDITOS", 450, 80, 40, ORANGE);
    
    DrawText("NARUTO NO MULTIVERSO", 250, 180, 30, YELLOW);
    
    DrawText("Desenvolvido por:", 400, 260, 25, WHITE);
    DrawText("Lucas Peluca", 450, 300, 25, ORANGE);
    DrawText("Samuel Pires", 450, 350, 25, ORANGE);
    DrawText("Rodrigo Gomes", 450, 400, 25, ORANGE);
    
    DrawText("Tecnologias:", 450, 480, 25, WHITE);
    DrawText("- Linguagem C", 480, 520, 20, LIGHTGRAY);
    DrawText("- Biblioteca Raylib 5.5", 480, 550, 20, LIGHTGRAY);
    
    DrawText("Pressione ESC ou clique para voltar", 350, 720, 25, ORANGE);
    
    EndDrawing();
}

typedef enum {
    MENU_PALAVRAS_PRINCIPAL,
    MENU_PALAVRAS_LISTAR,
    MENU_PALAVRAS_ADICIONAR,
    MENU_PALAVRAS_BUSCAR,
    MENU_PALAVRAS_ALTERAR,
    MENU_PALAVRAS_REMOVER
} EstadoMenuPalavras;

typedef struct {
    EstadoMenuPalavras estadoAtual;
    char inputPalavra[30];
    char inputDica[100];
    int inputTemaIndex;
    int inputDificuldade;
    int campoSelecionado;
    int indicePalavraEditando;
    int scrollOffset;
    char textoBusca[30];
} EstadoPalavras;

const char *temasDisponiveis[] = {"Dragon Ball", "One Piece", "Harry Potter", "Resident Evil", "Silent Hill"};
const int totalTemas = 5;

void desenharMenuPalavras(Texture2D imagemMenu, EstadoPalavras *estado, Palavra *listaPalavras, int totalPalavras, int *opcaoSelecionada) {
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (imagemMenu.id > 0) {
        DrawTexturePro(
            imagemMenu,
            (Rectangle){0, 0, (float)imagemMenu.width, (float)imagemMenu.height},
            (Rectangle){0, 0, 1200, 800},
            (Vector2){0, 0},
            0.0f,
            (Color){255, 255, 255, 100}
        );
    }
    
    DrawRectangle(0, 0, 1200, 800, (Color){0, 0, 0, 200});
    Vector2 posicaoMouse = GetMousePosition();
    
    switch (estado->estadoAtual) {
        case MENU_PALAVRAS_PRINCIPAL: {
            int larguraTitulo = MeasureText("GERENCIAR PALAVRAS", 40);
            DrawText("GERENCIAR PALAVRAS", (1200 - larguraTitulo) / 2, 50, 40, ORANGE);
            
            const char *opcoesPalavras[] = {"LISTAR TODAS", "ADICIONAR", "BUSCAR", "REMOVER", "VOLTAR"};
            int yInicial = 170;
            int espacamento = 70;
            
            for (int i = 0; i < 5; i++) {
                int y = yInicial + (i * espacamento);
                Rectangle botao = {400, (float)y, 400, 60};
                
                Color cor = WHITE;
                Color corFundo = (Color){30, 30, 30, 220};
                if (CheckCollisionPointRec(posicaoMouse, botao)) {
                    cor = ORANGE;
                    corFundo = (Color){60, 60, 60, 240};
                    *opcaoSelecionada = i;
                }
                
                DrawRectangleRec(botao, corFundo);
                DrawRectangleLinesEx(botao, 2, cor);
                int larguraTexto = MeasureText(opcoesPalavras[i], 25);
                DrawText(opcoesPalavras[i], 600 - larguraTexto/2, y + 18, 25, cor);
            }
            
            const char *textoTotal = TextFormat("Total de palavras: %d", totalPalavras);
            int larguraTotal = MeasureText(textoTotal, 25);
            DrawText(textoTotal, (1200 - larguraTotal) / 2, 580, 25, YELLOW);
            break;
        }
        
        case MENU_PALAVRAS_LISTAR: {
            int larguraLista = MeasureText("LISTA DE PALAVRAS", 35);
            DrawText("LISTA DE PALAVRAS", (1200 - larguraLista) / 2, 30, 35, ORANGE);
            
            int yInicio = 80;
            int linhasPorPagina = 15;
            int totalPaginas = (totalPalavras + linhasPorPagina - 1) / linhasPorPagina;
            int paginaAtual = estado->scrollOffset / linhasPorPagina;
            
            for (int i = estado->scrollOffset; i < estado->scrollOffset + linhasPorPagina && i < totalPalavras; i++) {
                int y = yInicio + ((i - estado->scrollOffset) * 35);
                
                Color corTexto = WHITE;
                if (i % 2 == 0) {
                    DrawRectangle(50, y - 2, 1100, 30, (Color){40, 40, 40, 100});
                }
                
                DrawText(TextFormat("%d.", i + 1), 60, y, 20, LIGHTGRAY);
                DrawText(listaPalavras[i].palavra, 100, y, 20, corTexto);
                DrawText(listaPalavras[i].dica, 250, y, 18, GRAY);
                DrawText(TextFormat("Dif: %d", listaPalavras[i].dificuldade), 650, y, 18, YELLOW);
                DrawText(listaPalavras[i].tema, 750, y, 18, GREEN);
            }
            
            // Controles de paginação
            if (totalPaginas > 1) {
                DrawText(TextFormat("Página %d de %d", paginaAtual + 1, totalPaginas), 500, 650, 20, ORANGE);
                DrawText("Use SETAS para navegar", 450, 680, 18, LIGHTGRAY);
            }
            
            int larguraEscLista = MeasureText("Pressione ESC para voltar", 20);
            DrawText("Pressione ESC para voltar", (1200 - larguraEscLista) / 2, 720, 20, ORANGE);
            break;
        }
        
        case MENU_PALAVRAS_ADICIONAR: {
            int larguraAdicionar = MeasureText("ADICIONAR NOVA PALAVRA", 35);
            DrawText("ADICIONAR NOVA PALAVRA", (1200 - larguraAdicionar) / 2, 30, 35, ORANGE);
            
            // Campo Palavra
            DrawText("Palavra:", 200, 120, 25, YELLOW);
            Rectangle campoPalavra = {200, 155, 600, 40};
            Color corCampoPalavra = (estado->campoSelecionado == 0) ? ORANGE : DARKGRAY;
            DrawRectangle(campoPalavra.x, campoPalavra.y, campoPalavra.width, campoPalavra.height, (Color){20, 20, 20, 200});
            DrawRectangleLinesEx(campoPalavra, 2, corCampoPalavra);
            DrawText(estado->inputPalavra, 210, 165, 20, WHITE);
            if (estado->campoSelecionado == 0 && ((int)(GetTime() * 2) % 2)) {
                int textWidth = MeasureText(estado->inputPalavra, 20);
                DrawText("_", 210 + textWidth, 165, 20, WHITE);
            }
            
            // Campo Dica
            DrawText("Dica:", 200, 220, 25, YELLOW);
            Rectangle campoDica = {200, 255, 600, 40};
            Color corCampoDica = (estado->campoSelecionado == 1) ? ORANGE : DARKGRAY;
            DrawRectangle(campoDica.x, campoDica.y, campoDica.width, campoDica.height, (Color){20, 20, 20, 200});
            DrawRectangleLinesEx(campoDica, 2, corCampoDica);
            DrawText(estado->inputDica, 210, 265, 20, WHITE);
            if (estado->campoSelecionado == 1 && ((int)(GetTime() * 2) % 2)) {
                int textWidth = MeasureText(estado->inputDica, 20);
                DrawText("_", 210 + textWidth, 265, 20, WHITE);
            }
            
            // Seleção de Tema
            DrawText("Tema:", 200, 320, 25, YELLOW);
            for (int i = 0; i < totalTemas; i++) {
                Rectangle botaoTema = {200 + (i * 130), 355, 120, 35};
                Color corTema = DARKGRAY;
                Color corFundoTema = (Color){20, 20, 20, 200};
                
                if (estado->inputTemaIndex == i) {
                    corTema = ORANGE;
                    corFundoTema = (Color){60, 60, 60, 240};
                } else if (CheckCollisionPointRec(posicaoMouse, botaoTema)) {
                    corTema = YELLOW;
                    corFundoTema = (Color){40, 40, 40, 220};
                }
                
                DrawRectangleRec(botaoTema, corFundoTema);
                DrawRectangleLinesEx(botaoTema, 2, corTema);
                int larguraTexto = MeasureText(temasDisponiveis[i], 14);
                DrawText(temasDisponiveis[i], botaoTema.x + (botaoTema.width - larguraTexto)/2, botaoTema.y + 10, 14, corTema);
            }
            
            // Campo Dificuldade
            DrawText("Dificuldade:", 200, 420, 25, YELLOW);
            for (int i = 1; i <= 3; i++) {
                Rectangle botaoDif = {200 + ((i-1) * 80), 455, 60, 35};
                Color corDif = DARKGRAY;
                Color corFundoDif = (Color){20, 20, 20, 200};
                
                if (estado->inputDificuldade == i) {
                    corDif = GREEN;
                    corFundoDif = (Color){0, 100, 0, 240};
                } else if (CheckCollisionPointRec(posicaoMouse, botaoDif)) {
                    corDif = YELLOW;
                    corFundoDif = (Color){40, 40, 40, 220};
                }
                
                DrawRectangleRec(botaoDif, corFundoDif);
                DrawRectangleLinesEx(botaoDif, 2, corDif);
                DrawText(TextFormat("%d", i), botaoDif.x + 25, botaoDif.y + 10, 20, corDif);
            }
            
            // Mensagem de erro se houver letras repetidas
            bool temLetrasRepetidas = false;
            if (strlen(estado->inputPalavra) > 1) {
                for (int i = 0; i < (int)strlen(estado->inputPalavra); i++) {
                    for (int j = i + 1; j < (int)strlen(estado->inputPalavra); j++) {
                        if (toupper(estado->inputPalavra[i]) == toupper(estado->inputPalavra[j])) {
                            temLetrasRepetidas = true;
                            break;
                        }
                    }
                    if (temLetrasRepetidas) break;
                }
            }
            
            if (temLetrasRepetidas) {
                DrawText("ERRO: A palavra não pode ter letras repetidas!", 250, 510, 20, RED);
            }
            
            // Botão Salvar
            Rectangle botaoSalvar = {335, 530, 150, 50};
            Color corSalvar = temLetrasRepetidas ? GRAY : DARKGRAY;
            Color corFundoSalvar = temLetrasRepetidas ? (Color){40, 40, 40, 200} : (Color){20, 80, 20, 200};
            if (!temLetrasRepetidas && CheckCollisionPointRec(posicaoMouse, botaoSalvar)) {
                corSalvar = GREEN;
                corFundoSalvar = (Color){30, 120, 30, 240};
            }
            DrawRectangleRec(botaoSalvar, corFundoSalvar);
            DrawRectangleLinesEx(botaoSalvar, 2, corSalvar);
            DrawText("SALVAR", 380, 550, 25, corSalvar);
            
            // Botão Cancelar
            Rectangle botaoCancelar = {505, 530, 150, 50};
            Color corCancelar = DARKGRAY;
            Color corFundoCancelar = (Color){80, 20, 20, 200};
            if (CheckCollisionPointRec(posicaoMouse, botaoCancelar)) {
                corCancelar = RED;
                corFundoCancelar = (Color){120, 30, 30, 240};
            }
            DrawRectangleRec(botaoCancelar, corFundoCancelar);
            DrawRectangleLinesEx(botaoCancelar, 2, corCancelar);
            DrawText("CANCELAR", 540, 550, 25, corCancelar);
            
            int larguraTab = MeasureText("Use TAB para navegar entre campos", 18);
            DrawText("Use TAB para navegar entre campos", (1200 - larguraTab) / 2, 630, 18, LIGHTGRAY);
            int larguraEnter = MeasureText("ENTER para salvar, ESC para cancelar", 18);
            DrawText("ENTER para salvar, ESC para cancelar", (1200 - larguraEnter) / 2, 660, 18, LIGHTGRAY);
            break;
        }
        
        case MENU_PALAVRAS_BUSCAR: {
            int larguraBuscar = MeasureText("BUSCAR PALAVRA", 35);
            DrawText("BUSCAR PALAVRA", (1200 - larguraBuscar) / 2, 30, 35, ORANGE);
            
            DrawText("Digite a palavra:", 200, 120, 25, YELLOW);
            Rectangle campoBusca = {200, 160, 600, 40};
            DrawRectangleLinesEx(campoBusca, 2, ORANGE);
            DrawText(estado->textoBusca, 210, 170, 20, WHITE);
            
            if ((int)(GetTime() * 2) % 2) {
                int textWidth = MeasureText(estado->textoBusca, 20);
                DrawText("_", 210 + textWidth, 170, 20, WHITE);
            }
            
            // Mostra resultado da busca se houver
            if (strlen(estado->textoBusca) > 0) {
                int indice = buscarPalavra(listaPalavras, totalPalavras, estado->textoBusca);
                if (indice >= 0) {
                    int larguraEncontradaBusca = MeasureText("PALAVRA ENCONTRADA:", 25);
                    DrawText("PALAVRA ENCONTRADA:", (1200 - larguraEncontradaBusca) / 2, 250, 25, GREEN);
                    DrawText(TextFormat("Palavra: %s", listaPalavras[indice].palavra), 320, 290, 20, WHITE);
                    DrawText(TextFormat("Dica: %s", listaPalavras[indice].dica), 320, 320, 20, WHITE);
                    DrawText(TextFormat("Dificuldade: %d", listaPalavras[indice].dificuldade), 320, 350, 20, WHITE);
                    DrawText(TextFormat("Tema: %s", listaPalavras[indice].tema), 320, 380, 20, WHITE);
                } else {
                    int larguraNaoEncontradaBusca = MeasureText("Palavra não encontrada", 25);
                    DrawText("Palavra não encontrada", (1200 - larguraNaoEncontradaBusca) / 2, 250, 25, RED);
                }
            }
            
            int larguraEscBusca = MeasureText("Pressione ESC para voltar", 20);
            DrawText("Pressione ESC para voltar", (1200 - larguraEscBusca) / 2, 600, 20, ORANGE);
            break;
        }
        
        case MENU_PALAVRAS_REMOVER: {
            int larguraRemover = MeasureText("REMOVER PALAVRA", 35);
            DrawText("REMOVER PALAVRA", (1200 - larguraRemover) / 2, 30, 35, RED);
            
            int larguraDigite = MeasureText("Digite a palavra a ser removida:", 25);
            DrawText("Digite a palavra a ser removida:", (1200 - larguraDigite) / 2, 120, 25, YELLOW);
            
            Rectangle campoRemover = {300, 160, 600, 40};
            DrawRectangle(campoRemover.x, campoRemover.y, campoRemover.width, campoRemover.height, (Color){20, 20, 20, 200});
            DrawRectangleLinesEx(campoRemover, 2, RED);
            DrawText(estado->textoBusca, 310, 170, 20, WHITE);
            
            if ((int)(GetTime() * 2) % 2) {
                int textWidth = MeasureText(estado->textoBusca, 20);
                DrawText("_", 310 + textWidth, 170, 20, WHITE);
            }
            
            // Mostra resultado da busca se houver
            if (strlen(estado->textoBusca) > 0) {
                int indice = buscarPalavra(listaPalavras, totalPalavras, estado->textoBusca);
                if (indice >= 0) {
                    int larguraEncontrada = MeasureText("PALAVRA ENCONTRADA:", 25);
                    DrawText("PALAVRA ENCONTRADA:", (1200 - larguraEncontrada) / 2, 250, 25, YELLOW);
                    
                    DrawRectangle(280, 290, 640, 120, (Color){40, 40, 40, 200});
                    DrawRectangleLinesEx((Rectangle){280, 290, 640, 120}, 2, YELLOW);
                    
                    DrawText(TextFormat("Palavra: %s", listaPalavras[indice].palavra), 300, 310, 20, WHITE);
                    DrawText(TextFormat("Dica: %s", listaPalavras[indice].dica), 300, 335, 18, LIGHTGRAY);
                    DrawText(TextFormat("Dificuldade: %d", listaPalavras[indice].dificuldade), 300, 360, 18, LIGHTGRAY);
                    DrawText(TextFormat("Tema: %s", listaPalavras[indice].tema), 300, 385, 18, LIGHTGRAY);
                    
                    // Botão Confirmar Remoção (centralizado)
                    Rectangle botaoConfirmar = {460, 430, 180, 50};
                    Color corConfirmar = RED;
                    Color corFundoConfirmar = (Color){80, 20, 20, 200};
                    if (CheckCollisionPointRec(posicaoMouse, botaoConfirmar)) {
                        corFundoConfirmar = (Color){120, 30, 30, 240};
                    }
                    
                    DrawRectangleRec(botaoConfirmar, corFundoConfirmar);
                    DrawRectangleLinesEx(botaoConfirmar, 2, corConfirmar);
                    int larguraConfirmar = MeasureText("CONFIRMAR", 20);
                    DrawText("CONFIRMAR", botaoConfirmar.x + (botaoConfirmar.width - larguraConfirmar) / 2, 440, 20, corConfirmar);
                    int larguraRemocao = MeasureText("REMOCAO", 16);
                    DrawText("REMOCAO", botaoConfirmar.x + (botaoConfirmar.width - larguraRemocao) / 2, 460, 16, corConfirmar);
                } else {
                    int larguraNaoEncontrada = MeasureText("Palavra não encontrada", 25);
                    DrawText("Palavra não encontrada", (1200 - larguraNaoEncontrada) / 2, 250, 25, RED);
                }
            }
            
            int larguraVoltar = MeasureText("Pressione ESC para voltar", 20);
            DrawText("Pressione ESC para voltar", (1200 - larguraVoltar) / 2, 580, 20, ORANGE);
            break;
        }
    }
    
    EndDrawing();
}

int main(void){
    // carrega palavras
    Palavra *listaPalavras = NULL;
    int totalPalavras = 0;
    
    printf("==============================================\n");
    printf("   NARUTO NO MULTIVERSO \n");
    printf("==============================================\n");
    printf(">> Carregando palavras...\n");
    
    carregarPalavrasIniciais(&listaPalavras, &totalPalavras);
    printf(">> %d palavras carregadas com sucesso!\n", totalPalavras);
    
    EstadoInterface estadoInterface ={0};
    inicializarInterface(&estadoInterface);
    
    Texture2D imagemMenu ={0};
    if (FileExists("assets/imagens/Terreno/Menu.png")){
        imagemMenu = LoadTexture("assets/imagens/Terreno/Menu.png");
    }
    
    Texture2D imagemMenuFases ={0};
    if (FileExists("assets/imagens/Terreno/MenuFases.png")){
        imagemMenuFases = LoadTexture("assets/imagens/Terreno/MenuFases.png");
    }
    
    RecursosCinematica recursosCinematica;
    carregarRecursosCinematica(&recursosCinematica);
    
    EstadoJogo estado;
    memset(&estado, 0, sizeof(EstadoJogo));
    carregarProgresso(&estado);
    
    EstadoCinematicas estadosCinematicas ={0};
    
    // Estado para gerenciamento de palavras
    EstadoPalavras estadoPalavras = {0};
    estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
    estadoPalavras.inputDificuldade = 1;
    int opcaoPalavrasSelecionada = 0;
    
    EstadoTela telaAtual = TELA_MENU_INICIAL;
    int faseSelecionada = 1;
    int opcaoMenuSelecionada = 0;
    
    // loop principal
    while (!WindowShouldClose() && telaAtual != TELA_SAIR){
        
        switch (telaAtual){
            case TELA_MENU_INICIAL:{
                desenharMenuInicial(imagemMenu, &opcaoMenuSelecionada);
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    switch (opcaoMenuSelecionada){
                        case 0:
                            telaAtual = TELA_MENU;
                            break;
                        case 1:
                            telaAtual = TELA_PALAVRAS;
                            estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                            break;
                        case 2:
                            telaAtual = TELA_INSTRUCOES;
                            break;
                        case 3:
                            telaAtual = TELA_CREDITOS;
                            break;
                        case 4:
                            telaAtual = TELA_SAIR;
                            break;
                    }
                }
                break;
            }
            
            case TELA_INSTRUCOES:{
                desenharInstrucoes(imagemMenu);
                
                if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    telaAtual = TELA_MENU_INICIAL;
                }
                break;
            }
            
            case TELA_CREDITOS:{
                desenharCreditos(imagemMenu);
                
                if (IsKeyPressed(KEY_ESCAPE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    telaAtual = TELA_MENU_INICIAL;
                }
                break;
            }
            
            case TELA_PALAVRAS:{
                desenharMenuPalavras(imagemMenu, &estadoPalavras, listaPalavras, totalPalavras, &opcaoPalavrasSelecionada);
                
                // Tratamento de entrada para o menu de palavras
                if (estadoPalavras.estadoAtual == MENU_PALAVRAS_PRINCIPAL) {
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        switch (opcaoPalavrasSelecionada) {
                            case 0: // Listar todas
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_LISTAR;
                                estadoPalavras.scrollOffset = 0;
                                break;
                            case 1: // Adicionar
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_ADICIONAR;
                                memset(estadoPalavras.inputPalavra, 0, sizeof(estadoPalavras.inputPalavra));
                                memset(estadoPalavras.inputDica, 0, sizeof(estadoPalavras.inputDica));
                                estadoPalavras.inputTemaIndex = 0;
                                estadoPalavras.inputDificuldade = 1;
                                estadoPalavras.campoSelecionado = 0;
                                break;
                            case 2: // Buscar
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_BUSCAR;
                                memset(estadoPalavras.textoBusca, 0, sizeof(estadoPalavras.textoBusca));
                                break;
                            case 3: // Remover
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_REMOVER;
                                memset(estadoPalavras.textoBusca, 0, sizeof(estadoPalavras.textoBusca));
                                break;
                            case 4: // Voltar
                                telaAtual = TELA_MENU_INICIAL;
                                break;
                        }
                    }
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        telaAtual = TELA_MENU_INICIAL;
                    }
                } 
                else if (estadoPalavras.estadoAtual == MENU_PALAVRAS_LISTAR) {
                    // Navegação na lista
                    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT)) {
                        if (estadoPalavras.scrollOffset + 15 < totalPalavras) {
                            estadoPalavras.scrollOffset += 15;
                        }
                    }
                    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT)) {
                        if (estadoPalavras.scrollOffset >= 15) {
                            estadoPalavras.scrollOffset -= 15;
                        } else {
                            estadoPalavras.scrollOffset = 0;
                        }
                    }
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                    }
                }
                else if (estadoPalavras.estadoAtual == MENU_PALAVRAS_ADICIONAR) {
                    // Navegação entre campos
                    if (IsKeyPressed(KEY_TAB)) {
                        estadoPalavras.campoSelecionado = (estadoPalavras.campoSelecionado + 1) % 2; // Apenas palavra e dica
                    }
                    
                    // Input de texto
                    int key = GetCharPressed();
                    while (key > 0) {
                        if (estadoPalavras.campoSelecionado == 0 && strlen(estadoPalavras.inputPalavra) < 29) {
                            if (key >= 32 && key <= 126) {
                                char str[2] = {(char)key, '\0'};
                                strcat(estadoPalavras.inputPalavra, str);
                            }
                        }
                        else if (estadoPalavras.campoSelecionado == 1 && strlen(estadoPalavras.inputDica) < 99) {
                            if (key >= 32 && key <= 126) {
                                char str[2] = {(char)key, '\0'};
                                strcat(estadoPalavras.inputDica, str);
                            }
                        }
                        key = GetCharPressed();
                    }
                    
                    // Backspace
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        if (estadoPalavras.campoSelecionado == 0) {
                            int len = strlen(estadoPalavras.inputPalavra);
                            if (len > 0) estadoPalavras.inputPalavra[len - 1] = '\0';
                        }
                        else if (estadoPalavras.campoSelecionado == 1) {
                            int len = strlen(estadoPalavras.inputDica);
                            if (len > 0) estadoPalavras.inputDica[len - 1] = '\0';
                        }
                    }
                    
                    // Salvar palavra
                    if (IsKeyPressed(KEY_ENTER)) {
                        if (strlen(estadoPalavras.inputPalavra) > 0 && strlen(estadoPalavras.inputDica) > 0) {
                            // Verificar letras repetidas
                            int temRepetidas = 0;
                            for (int i = 0; i < (int)strlen(estadoPalavras.inputPalavra); i++) {
                                for (int j = i + 1; j < (int)strlen(estadoPalavras.inputPalavra); j++) {
                                    if (toupper(estadoPalavras.inputPalavra[i]) == toupper(estadoPalavras.inputPalavra[j])) {
                                        temRepetidas = 1;
                                        break;
                                    }
                                }
                                if (temRepetidas) break;
                            }
                            
                            if (!temRepetidas) {
                                adicionarPalavraDireta(&listaPalavras, &totalPalavras, 
                                                     estadoPalavras.inputPalavra, 
                                                     estadoPalavras.inputDica, 
                                                     estadoPalavras.inputDificuldade, 
                                                     (char*)temasDisponiveis[estadoPalavras.inputTemaIndex]);
                                salvarPalavrasCSV(listaPalavras, totalPalavras, "assets/palavras.csv");
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                            }
                        }
                    }
                    
                    // Cliques nos botões e seleções
                    Vector2 mouse = GetMousePosition();
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        Rectangle botaoSalvar = {335, 530, 150, 50};
                        Rectangle botaoCancelar = {505, 530, 150, 50};
                        
                        if (CheckCollisionPointRec(mouse, botaoSalvar)) {
                            if (strlen(estadoPalavras.inputPalavra) > 0 && strlen(estadoPalavras.inputDica) > 0) {
                                // Verificar letras repetidas
                                int temRepetidas = 0;
                                for (int i = 0; i < (int)strlen(estadoPalavras.inputPalavra); i++) {
                                    for (int j = i + 1; j < (int)strlen(estadoPalavras.inputPalavra); j++) {
                                        if (toupper(estadoPalavras.inputPalavra[i]) == toupper(estadoPalavras.inputPalavra[j])) {
                                            temRepetidas = 1;
                                            break;
                                        }
                                    }
                                    if (temRepetidas) break;
                                }
                                
                                if (!temRepetidas) {
                                    adicionarPalavraDireta(&listaPalavras, &totalPalavras, 
                                                         estadoPalavras.inputPalavra, 
                                                         estadoPalavras.inputDica, 
                                                         estadoPalavras.inputDificuldade, 
                                                         (char*)temasDisponiveis[estadoPalavras.inputTemaIndex]);
                                    salvarPalavrasCSV(listaPalavras, totalPalavras, "assets/palavras.csv");
                                    estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                                }
                            }
                        }
                        else if (CheckCollisionPointRec(mouse, botaoCancelar)) {
                            estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                        }
                        else {
                            // Clique nos campos de entrada
                            Rectangle campoPalavra = {200, 155, 600, 40};
                            Rectangle campoDica = {200, 255, 600, 40};
                            
                            if (CheckCollisionPointRec(mouse, campoPalavra)) {
                                estadoPalavras.campoSelecionado = 0;
                            }
                            else if (CheckCollisionPointRec(mouse, campoDica)) {
                                estadoPalavras.campoSelecionado = 1;
                            }
                            
                            // Clique nos temas
                            for (int i = 0; i < totalTemas; i++) {
                                Rectangle botaoTema = {200 + (i * 130), 355, 120, 35};
                                if (CheckCollisionPointRec(mouse, botaoTema)) {
                                    estadoPalavras.inputTemaIndex = i;
                                }
                            }
                            
                            // Clique na dificuldade
                            for (int i = 1; i <= 3; i++) {
                                Rectangle botaoDif = {200 + ((i-1) * 80), 455, 60, 35};
                                if (CheckCollisionPointRec(mouse, botaoDif)) {
                                    estadoPalavras.inputDificuldade = i;
                                }
                            }
                        }
                    }
                    
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                    }
                }
                else if (estadoPalavras.estadoAtual == MENU_PALAVRAS_BUSCAR) {
                    // Input para busca
                    int key = GetCharPressed();
                    while (key > 0) {
                        if (strlen(estadoPalavras.textoBusca) < 29) {
                            if (key >= 32 && key <= 126) {
                                char str[2] = {(char)key, '\0'};
                                strcat(estadoPalavras.textoBusca, str);
                            }
                        }
                        key = GetCharPressed();
                    }
                    
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        int len = strlen(estadoPalavras.textoBusca);
                        if (len > 0) estadoPalavras.textoBusca[len - 1] = '\0';
                    }
                    
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                    }
                }
                else if (estadoPalavras.estadoAtual == MENU_PALAVRAS_REMOVER) {
                    // Input para busca de palavra a ser removida
                    int key = GetCharPressed();
                    while (key > 0) {
                        if (strlen(estadoPalavras.textoBusca) < 29) {
                            if (key >= 32 && key <= 126) {
                                char str[2] = {(char)key, '\0'};
                                strcat(estadoPalavras.textoBusca, str);
                            }
                        }
                        key = GetCharPressed();
                    }
                    
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        int len = strlen(estadoPalavras.textoBusca);
                        if (len > 0) estadoPalavras.textoBusca[len - 1] = '\0';
                    }
                    
                    // Clique no botão de confirmar remoção
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strlen(estadoPalavras.textoBusca) > 0) {
                        int indice = buscarPalavra(listaPalavras, totalPalavras, estadoPalavras.textoBusca);
                        if (indice >= 0) {
                            Vector2 mouse = GetMousePosition();
                            Rectangle botaoConfirmar = {460, 430, 180, 50};
                            
                            if (CheckCollisionPointRec(mouse, botaoConfirmar)) {
                                removerPalavra(&listaPalavras, &totalPalavras, indice);
                                salvarPalavrasCSV(listaPalavras, totalPalavras, "assets/palavras.csv");
                                memset(estadoPalavras.textoBusca, 0, sizeof(estadoPalavras.textoBusca));
                                estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                            }
                        }
                    }
                    
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        estadoPalavras.estadoAtual = MENU_PALAVRAS_PRINCIPAL;
                    }
                }
                break;
            }
            
            case TELA_MENU:{
                BeginDrawing();
                int fase = desenharMenuFases(&estado, imagemMenuFases);
                EndDrawing();
                
                if (fase > 0){
                    faseSelecionada = fase;
                    // salva o progresso atual antes de entrar na fase
                    salvarProgresso(&estado);
                    // reseta o estado das cinemáticas ao selecionar uma nova fase
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    telaAtual = TELA_CINEMATICA;
                } else if (fase == -2){
                    resetarProgresso(&estado);
                }
                
                if (IsKeyPressed(KEY_ESCAPE)){
                    telaAtual = TELA_MENU_INICIAL;
                }
                break;
            }
            
            case TELA_CINEMATICA:{
                // executa cinemática de introdução da fase
                if (executarCinematicaIntro(&recursosCinematica, faseSelecionada, &estadosCinematicas)){
                    if(faseSelecionada != 1){
                        Palavra *palavra = selecionarPalavraAleatoria(
                            listaPalavras, 
                            totalPalavras, 
                            temasFases[faseSelecionada - 1]
                        );
                        
                        if (palavra != NULL){
                            inicializarJogo(&estado, palavra, faseSelecionada);
                            telaAtual = TELA_JOGO;
                        }
                    }else{
                        telaAtual = TELA_TRANSICAO;
                    }
                }
                
                if (IsKeyPressed(KEY_ESCAPE)){
                    // reseta o estado das cinemáticas ao voltar para o menu
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    // reseta completamente o estado do jogo
                    memset(&estado, 0, sizeof(EstadoJogo));
                    // recarrega o progresso do arquivo para restaurar fases desbloqueadas
                    carregarProgresso(&estado);
                    telaAtual = TELA_MENU;
                }
                break;
            }
            
            case TELA_JOGO:{
                // atualiza o cronômetro
                atualizarTempo(&estado, GetFrameTime());
                
                processarEntrada(&estado, &estadoInterface.teclado);
                
                Texture2D terrenoFase;
                Music musicaFase;
                switch(faseSelecionada){
                    case 2: terrenoFase = recursosCinematica.fases[1]; musicaFase = recursosCinematica.trilhaSonora[2]; break;
                    case 3: terrenoFase = recursosCinematica.fases[2]; musicaFase = recursosCinematica.trilhaSonora[3]; break;
                    case 4: terrenoFase = recursosCinematica.fases[3]; musicaFase = recursosCinematica.trilhaSonora[4]; break;
                    case 5: terrenoFase = recursosCinematica.fases[4]; musicaFase = recursosCinematica.trilhaSonora[5]; break;
                    case 6: terrenoFase = recursosCinematica.fases[5]; musicaFase = recursosCinematica.trilhaSonora[6]; break;
                    case 7: terrenoFase = recursosCinematica.fases[6]; musicaFase = recursosCinematica.trilhaSonora[7]; break;
                    default: terrenoFase = (Texture2D){0}; musicaFase = (Music){0}; break;
                }
                
                desenharJogo(&estado, terrenoFase, &estadoInterface);
                UpdateMusicStream(musicaFase);
                
                if (estado.venceu || estado.perdeu){
                    telaAtual = TELA_RESULTADO;
                }
                
                if (IsKeyPressed(KEY_ESCAPE)){
                    // reseta o estado das cinemáticas ao voltar para o menu
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    // reseta completamente o estado do jogo
                    memset(&estado, 0, sizeof(EstadoJogo));
                    // recarrega o progresso do arquivo para restaurar fases desbloqueadas
                    carregarProgresso(&estado);
                    telaAtual = TELA_MENU;
                }
                
                break;
            }
            
            case TELA_RESULTADO:{
                Texture2D terrenoFase;
                Music musicaFase;
                switch(faseSelecionada){
                    case 2: terrenoFase = recursosCinematica.fases[1]; musicaFase = recursosCinematica.trilhaSonora[2]; break;
                    case 3: terrenoFase = recursosCinematica.fases[2]; musicaFase = recursosCinematica.trilhaSonora[3]; break;
                    case 4: terrenoFase = recursosCinematica.fases[3]; musicaFase = recursosCinematica.trilhaSonora[4]; break;
                    case 5: terrenoFase = recursosCinematica.fases[4]; musicaFase = recursosCinematica.trilhaSonora[5]; break;
                    case 6: terrenoFase = recursosCinematica.fases[5]; musicaFase = recursosCinematica.trilhaSonora[6]; break;
                    case 7: terrenoFase = recursosCinematica.fases[6]; break;
                    default: terrenoFase = (Texture2D){0}; musicaFase = (Music){0}; break;
                }
                
                desenharJogo(&estado, terrenoFase, &estadoInterface);
                UpdateMusicStream(musicaFase);
                
                // aguarda o usuário apertar espaco para continuar
                if (IsKeyPressed(KEY_SPACE)){
                    if (estado.venceu){
                        // se venceu, vai para o buraco negro (transicao)
                        telaAtual = TELA_TRANSICAO;
                    } else{
                        // se perdeu, volta pra primeira fase
                        faseSelecionada = 1;
                        // NÃO reseta o progresso aqui mantém as fases desbloqueadas
                        memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                        telaAtual = TELA_CINEMATICA;
                    }
                }
                
                // ESC volta no menu
                if (IsKeyPressed(KEY_ESCAPE)){
                    // reseta o estado das cinemáticas ao voltar para o menu
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    // reseta completamente o estado do jogo
                    memset(&estado, 0, sizeof(EstadoJogo));
                    // recarrega o progresso do arquivo para restaurar fases desbloqueadas
                    carregarProgresso(&estado);
                    telaAtual = TELA_MENU;
                }
                
                break;
            }
            
            case TELA_TRANSICAO:{
                // executa cinemática de transição (narutinho indo ao buraco negro)
                if (executarCinematicaTransicao(&recursosCinematica, faseSelecionada, &estadosCinematicas)){
                    // marca a fase atual como concluída
                    estado.progressoFases[faseSelecionada - 1] = 2;
                    
                    // desbloqueia a próxima fase
                    if (faseSelecionada < 8 && estado.progressoFases[faseSelecionada] == 0){
                        estado.progressoFases[faseSelecionada] = 1;
                    }
                    
                    // salva o progresso
                    salvarProgresso(&estado);
                    
                    // transição terminou vai para o menu ou próxima fase
                    if (faseSelecionada < 8){
                        faseSelecionada++;
                        telaAtual = TELA_CINEMATICA; // próxima fase
                    } else{
                        // terminou todas as fases, vai para a tela de parabéns
                        telaAtual = TELA_PARABENS;
                    }
                }
                
                if (IsKeyPressed(KEY_ESCAPE)){
                    // reseta o estado das cinemáticas e jogo ao voltar para o menu
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    // reseta completamente o estado do jogo
                    memset(&estado, 0, sizeof(EstadoJogo));
                    // recarrega o progresso do arquivo para restaurar fases desbloqueadas
                    carregarProgresso(&estado);
                    telaAtual = TELA_MENU;
                }
                break;
            }
            
            case TELA_PARABENS:{
                BeginDrawing();
                ClearBackground(BLACK);
                
                // centraliza todos os textos
                int larguraParabens = MeasureText("PARABÉNS!", 70);
                DrawText("PARABÉNS!", (GetScreenWidth() - larguraParabens) / 2, 250, 70, GOLD);
                
                int larguraCompletou = MeasureText("Você completou todas as fases!", 34);
                DrawText("Você completou todas as fases!", (GetScreenWidth() - larguraCompletou) / 2, 350, 34, WHITE);
                
                int larguraDerrotou = MeasureText("Narutinho derrotou Elimur!", 30);
                DrawText("Narutinho derrotou Elimur!", (GetScreenWidth() - larguraDerrotou) / 2, 420, 30, GREEN);
                
                int larguraVoltar = MeasureText("Pressione ESPAÇO para voltar ao menu", 24);
                DrawText("Pressione ESPAÇO para voltar ao menu", (GetScreenWidth() - larguraVoltar) / 2, 520, 24, GRAY);
                
                EndDrawing();
                
                if (IsKeyPressed(KEY_SPACE)){
                    // reseta o estado das cinemáticas e jogo ao voltar para o menu
                    memset(&estadosCinematicas, 0, sizeof(EstadoCinematicas));
                    // reseta completamente o estado do jogo
                    memset(&estado, 0, sizeof(EstadoJogo));
                    // recarrega o progresso do arquivo para restaurar fases desbloqueadas
                    carregarProgresso(&estado);
                    telaAtual = TELA_MENU_INICIAL;
                }
                break;
            }
            
            default:
                break;
        }
    }
    
    // finaliza
    if (imagemMenu.id > 0){
        UnloadTexture(imagemMenu);
    }
    if (imagemMenuFases.id > 0){
        UnloadTexture(imagemMenuFases);
    }
    descarregarRecursosCinematica(&recursosCinematica);
    finalizarInterface();
    liberarPalavras(listaPalavras);
    
    printf("\n>> Jogo encerrado. Obrigado por jogar!\n");
    
    return 0;
}