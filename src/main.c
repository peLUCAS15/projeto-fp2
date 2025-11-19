#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h"
#include "jogo.h"
#include "interface.h"
#include "cinematica.h"

typedef enum{
    TELA_MENU_INICIAL,
    TELA_INSTRUCOES,
    TELA_CREDITOS,
    TELA_MENU,
    TELA_CINEMATICA,
    TELA_JOGO,
    TELA_RESULTADO,
    TELA_TRANSICAO,
    TELA_SAIR
} EstadoTela;

const char *temasFases[] ={
    "Dragon Ball",
    "One Piece",
    "Harry Potter",
    "Resident Evil",
    "Silent Hill",
    "Final"
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
    
    const char *opcoes[] ={"INICIAR", "INSTRUCOES", "CREDITOS", "SAIR"};
    int yInicial = 320;
    int espacamento = 90;
    int larguraBotao = 350;
    int alturaBotao = 65;
    
    for (int i = 0; i < 4; i++){
        int y = yInicial + (i * espacamento);
        Rectangle botao ={(1200 - larguraBotao) / 2, (float)y, (float)larguraBotao, (float)alturaBotao};
        
        Color cor = DARKGRAY;
        if (CheckCollisionPointRec(posicaoMouse, botao)){
            cor = ORANGE;
            *opcaoSelecionada = i;
            DrawRectangleRec(botao, (Color){255, 140, 0, 50});
        }
        
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
                            telaAtual = TELA_INSTRUCOES;
                            break;
                        case 2:
                            telaAtual = TELA_CREDITOS;
                            break;
                        case 3:
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
                    Palavra *palavra = selecionarPalavraAleatoria(
                        listaPalavras, 
                        totalPalavras, 
                        temasFases[faseSelecionada - 1]
                    );
                    
                    if (palavra != NULL){
                        inicializarJogo(&estado, palavra, faseSelecionada);
                        telaAtual = TELA_JOGO;
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
                processarEntrada(&estado, &estadoInterface.teclado);
                
                Texture2D terrenoFase;
                Music musicaFase;
                switch(faseSelecionada){
                    case 1: terrenoFase = recursosCinematica.fases[1]; musicaFase = recursosCinematica.trilhaSonora[2]; break;
                    case 2: terrenoFase = recursosCinematica.fases[2]; musicaFase = recursosCinematica.trilhaSonora[3]; break;
                    case 3: terrenoFase = recursosCinematica.fases[3]; musicaFase = recursosCinematica.trilhaSonora[4]; break;
                    case 4: terrenoFase = recursosCinematica.fases[4]; musicaFase = recursosCinematica.trilhaSonora[5]; break;
                    case 5: terrenoFase = recursosCinematica.fases[5]; musicaFase = recursosCinematica.trilhaSonora[6]; break;
                    case 6: terrenoFase = recursosCinematica.fases[6]; break;
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
                    case 1: terrenoFase = recursosCinematica.fases[1]; musicaFase = recursosCinematica.trilhaSonora[2]; break;
                    case 2: terrenoFase = recursosCinematica.fases[2]; musicaFase = recursosCinematica.trilhaSonora[3]; break;
                    case 3: terrenoFase = recursosCinematica.fases[3]; musicaFase = recursosCinematica.trilhaSonora[4]; break;
                    case 4: terrenoFase = recursosCinematica.fases[4]; musicaFase = recursosCinematica.trilhaSonora[5]; break;
                    case 5: terrenoFase = recursosCinematica.fases[5]; musicaFase = recursosCinematica.trilhaSonora[6]; break;
                    case 6: terrenoFase = recursosCinematica.fases[6]; break;
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
                    if (faseSelecionada < 6 && estado.progressoFases[faseSelecionada] == 0){
                        estado.progressoFases[faseSelecionada] = 1;
                    }
                    
                    // salva o progresso
                    salvarProgresso(&estado);
                    
                    // transição terminou vai para o menu ou próxima fase
                    if (faseSelecionada < 6){
                        faseSelecionada++;
                        telaAtual = TELA_CINEMATICA; // próxima fase
                    } else{
                        // terminou as fases
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
                            telaAtual = TELA_MENU;
                        }
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