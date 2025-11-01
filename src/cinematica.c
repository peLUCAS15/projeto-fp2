#include "cinematica.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>

bool carregarRecursosCinematica(RecursosCinematica *recursos){
    memset(recursos, 0, sizeof(RecursosCinematica));
    
    if (FileExists("assets/imagens/Terreno/DragonBall.png")){
        Image img = LoadImage("assets/imagens/Terreno/DragonBall.png");
        ImageResize(&img, 1200, 800);
        recursos->faseDragonBallTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/OnePiece.png")){
        Image img = LoadImage("assets/imagens/Terreno/OnePiece.png");
        ImageResize(&img, 1200, 800);
        recursos->faseOnePieceTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/Hogwarts.png")){
        Image img = LoadImage("assets/imagens/Terreno/Hogwarts.png");
        ImageResize(&img, 1200, 800);
        recursos->faseHarryPotterTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/ResidentEvil.png")){
        Image img = LoadImage("assets/imagens/Terreno/ResidentEvil.png");
        ImageResize(&img, 1200, 800);
        recursos->faseResidentEvilTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/SilentHill.png")){
        Image img = LoadImage("assets/imagens/Terreno/SilentHill.png");
        ImageResize(&img, 1200, 800);
        recursos->faseSilentHillTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega sprites do narutinho
    if (FileExists("assets/imagens/Sprite/NarutinhoParado.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutinhoParado.png");
        ImageResize(&img, 180, 180);
        recursos->narutoParado = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutoAndando.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoAndando.png");
        ImageResize(&img, 180, 180);
        recursos->narutoAndando = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutinhoCorrendo.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutinhoCorrendo.png");
        ImageResize(&img, 180, 180);
        recursos->narutoCorrendo = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutoPulando.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoPulando.png");
        ImageResize(&img, 180, 180);
        recursos->narutoPulando = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutinhoFalando.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutinhoFalando.png");
        ImageResize(&img, 240, 240);
        recursos->narutoFalando = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega sprites do elimur 
    if (FileExists("assets/imagens/Sprite/ElimurParado.png")){
        Image img = LoadImage("assets/imagens/Sprite/ElimurParado.png");
        ImageResize(&img, 300, 300);
        recursos->elimurParado = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/ElimurDialogo.png")){
        Image img = LoadImage("assets/imagens/Sprite/ElimurDialogo.png");
        ImageResize(&img, 240, 240);  // Mesmo tamanho do Naruto falando
        recursos->elimurFalando = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega caixa de diálogo
    if (FileExists("assets/imagens/Caixas/DialogoNaruto.png")){
        Image img = LoadImage("assets/imagens/Caixas/DialogoNaruto.png");
        ImageResize(&img, 1936, 1440);
        recursos->caixaDialogo = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega buraco negro 
    if (FileExists("assets/imagens/Terreno/BuracoNegro.png")){
        Image img = LoadImage("assets/imagens/Terreno/BuracoNegro.png");
        ImageResize(&img, 350, 350);
        recursos->buracoNegro = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega música
    if (FileExists("assets/audio/BattleTrainerK.ogg")){
        recursos->musicaFundo = LoadMusicStream("assets/audio/BattleTrainerK.ogg");
        SetMusicVolume(recursos->musicaFundo, 0.5f);
        PlayMusicStream(recursos->musicaFundo);
    }
    
    recursos->carregado = true;
    return true;
}

void descarregarRecursosCinematica(RecursosCinematica *recursos){
    if (!recursos->carregado) return;
    
    UnloadTexture(recursos->faseDragonBallTerreno);
    UnloadTexture(recursos->faseOnePieceTerreno);
    UnloadTexture(recursos->faseHarryPotterTerreno);
    UnloadTexture(recursos->faseResidentEvilTerreno);
    UnloadTexture(recursos->faseSilentHillTerreno);
    UnloadTexture(recursos->narutoParado);
    UnloadTexture(recursos->narutoAndando);
    UnloadTexture(recursos->narutoCorrendo);
    UnloadTexture(recursos->narutoPulando);
    UnloadTexture(recursos->narutoFalando);
    UnloadTexture(recursos->elimurParado);
    UnloadTexture(recursos->elimurFalando);
    UnloadTexture(recursos->caixaDialogo);
    UnloadTexture(recursos->buracoNegro);
    UnloadMusicStream(recursos->musicaFundo);
    
    recursos->carregado = false;
}

void inicializarCinematica(EstadoCinematica *estado, int fase){
    memset(estado, 0, sizeof(EstadoCinematica));
    estado->fase = fase;
    estado->narutoX = 0.0f;
    estado->narutoY = 0.0f;
    estado->cinematicaAtiva = true;
    estado->dialogoAtual = 0;
}

const char* dialogos_fase1[] ={
    "NARRADOR: Narutinho se vê preso em lugar totalmente desconhecido|uma energia diferente paira no ar",
    "Narutinho: O que houve?? Onde estou?? Esse chakra… não espera|acho que é Ki?! Será que eu virarei um Sayajin de nove caudas?!",
    "Elimur: Agora vou conquistar todos os universos finalmente,|espero que o Narutinho erre esta palavras chave,|para que eu domine este universo.",
    "JOGO"
};

const char* dialogos_fase2[] ={
    "NARRADOR: Narutinho conseguiu encontrar a primeira palavra,|e com isso ele e levado a um novo mundo. Um lugar cercado por mar",
    "e criaturas nunca vistas. As frutas do diabo dominam o lugar,|e uma era de Pirataria deixam as coisas mais perigosoas para ele.",
    "NARUTO: Gomu Gomu No Rasengan, não pera pera pera.|Agora sou o pirata mais forte do mundo. Irei desafiar o|Barba Negra, a Marinha e por fim acabar com você Elimur.",
    "ELIMUR: Você conseguiu acertar a palavra anterior,|mas esta não há fruta do diabo que ira te ajude.|Ninja ou Pirata, nenhum irá garantir sua vitória.",
    "JOGO"
};

const char* dialogos_fase3[] ={
    "NARRADOR: Mesmo conseguindo decifrar mais uma palavra,|Narutinho se vê preso em um mundo de magia agora|ele, terá que enfrentar um mal que não deve ser nomeado,",
    "e impedir Elimur de fazer um pacto com esse novo ser.|Pois quando dois Mal distinto se une, coisa boa não deve acontecer",
    "NARUTO: Pela minha varinha, lá ele,  e agora, onde estou????|multiplos clones das sombras.... Será ilusão ou mágia???",
    "ELIMUR: Não estou gostando deste desfecho, acho que preciso|me juntar a Valdemort para conquistar meus objetivos. Quem sabe|um Avada Kedavra no Narutinho dê um jeito em tudo isso",
    "JOGO"
};

const char* dialogos_fase4[] ={
    "Depois de escapar (mais ou menos) da escola de magia, Narutinho dá de|cara com um lugar... morto demais para estar vivo. Ruelas escuras, gemidos|estranhos e cheiro de laboratório mal higienizado. Sim, ele caiu em",
    "um mundo infestado pelos erros da ciência: bem-vindo à cidade dos|zumbis, bem-vindo à Raccoon City. Enquanto tenta entender o que é um|T-vírus ele percebe que a palavra-chave pode estar no coração da|Umbrella Corporation... ou no cérebro de algum zumbi esfomeado.",
    "NARUTO: Que tipo de invocação é essa? Esses 'caras' não têm nem|chakra ECA, esse tentou me morder! Clones... com desinfetante, já!",
    "ELIMUR: Eles não correm, mas também não cansam...|perfeito para os meus planos. Se o Valdemort falhou, talvez esses|mortos-vivos consigam deter Narutinho.",
    "JOGO"
};

const char* dialogos_fase5[] ={
    "NARRADOR: A névoa desce. O silêncio grita. Narutinho|mal consegue enxergar dois passos à frente — e o que vê...| talvez preferisse não ter visto. Ele entrou em Silent Hill,|um lugar onde os medos ganham forma e os pecados têm rosto.",
    "Aqui, a realidade se retorce e os monstros vêm de dentro. A chave|para sair pode estar escondida nos cantos mais sombrios da própria alma...|ou atrás daquele espelho que definitivamente não estava ali antes.",
    "NARUTO: Ei... isso é um Genjutsu? Por que minha sombra|está chorando? E quem acendeu essa sirene?! Ah não, de novo não...",
    "ELIMUR: Heh... este lugar sabe explorar os medos. Talvez nem|precise lutar. Que o próprio Narutinho se destrua por dentro.",
    "JOGO"
};

bool executarCinematicaIntro(RecursosCinematica *recursos, int fase, EstadoCinematicas *estados){
    if (!estados->estadoIntro.inicializado){
        inicializarCinematica(&estados->estadoIntro, fase);
        estados->estadoIntro.inicializado = true;
    }
    
    // atualiza música
    UpdateMusicStream(recursos->musicaFundo);
    
    Texture2D terreno;
    const char **dialogos;
    int numeroDialogos;
    float narutoBaseY = 320;
    
    switch(fase){
        case 1:
            terreno = recursos->faseDragonBallTerreno;
            dialogos = dialogos_fase1;
            numeroDialogos = 4;
            narutoBaseY = 360;
            break;
        case 2:
            terreno = recursos->faseOnePieceTerreno;
            dialogos = dialogos_fase2;
            numeroDialogos = 5;
            narutoBaseY = 320;
            break;
        case 3:
            terreno = recursos->faseHarryPotterTerreno;
            dialogos = dialogos_fase3;
            numeroDialogos = 5;
            narutoBaseY = 360;
            break;
        case 4:
            terreno = recursos->faseResidentEvilTerreno;
            dialogos = dialogos_fase4;
            numeroDialogos = 5;
            narutoBaseY = 360;
            break;
        case 5:
            terreno = recursos->faseSilentHillTerreno;
            dialogos = dialogos_fase5;
            numeroDialogos = 5;
            narutoBaseY = 360;
            break;
        default:
            return true;
    }
    
    // narutinho entrando
    if (estados->estadoIntro.narutoX < 300){
        estados->estadoIntro.narutoX += 2.0f;
    }
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawTexture(terreno, 0, 0, WHITE);
    
    DrawTexture(recursos->elimurParado, 900, narutoBaseY, WHITE);
    
    if (estados->estadoIntro.narutoX < 300){
        DrawTexture(recursos->narutoCorrendo, estados->estadoIntro.narutoX, narutoBaseY, WHITE);
    } else{
        DrawTexture(recursos->narutoParado, estados->estadoIntro.narutoX, narutoBaseY, WHITE);
    }
    
    if (estados->estadoIntro.dialogoAtual < numeroDialogos && estados->estadoIntro.narutoX >= 300){
        const char *dialogo = dialogos[estados->estadoIntro.dialogoAtual];
        
        // desenha caixa de diálogo 
        DrawTexture(recursos->caixaDialogo, 0, 172, WHITE);
        
        // identifica quem está falando
        bool narutoFala = (strncmp(dialogo, "NARUTO", 6) == 0 || strncmp(dialogo, "Narutinho", 9) == 0);
        bool elimurFala = (strncmp(dialogo, "ELIMUR", 6) == 0 || strncmp(dialogo, "Elimur", 6) == 0);
        
        // desenha o personagem que está falando 
        if (narutoFala){
            DrawTexture(recursos->narutoFalando, 20, 460, WHITE);
        } else if (elimurFala){
            DrawTexture(recursos->elimurFalando, 920, 460, WHITE);
        }
        
        // desenha o texto do diálogo 
        char buffer[500];
        strcpy(buffer, dialogo);
        int y = 720;
        
        char *linha = strtok(buffer, "|");
        while (linha != NULL && y < GetScreenHeight() - 10){
            DrawText(linha, 40, y, 24, BLACK);
            y += 26;
            linha = strtok(NULL, "|");
        }
        
        if (IsKeyPressed(KEY_ENTER)){
            estados->estadoIntro.dialogoAtual++;
        }
    }
    
    if (estados->estadoIntro.dialogoAtual >= numeroDialogos - 1){
        const char *texto = "Pressione ESPACO para começar o desafio!";
        int larguraTexto = MeasureText(texto, 24);
        DrawText(texto, (GetScreenWidth() - larguraTexto) / 2, 30, 24, YELLOW);
        if (IsKeyPressed(KEY_SPACE)){
            estados->estadoIntro.inicializado = false;
            estados->estadoIntro.dialogoAtual = 0;
            estados->estadoIntro.narutoX = 0;
            EndDrawing();
            return true;
        }
    }
    
    EndDrawing();
    return false;
}

bool executarCinematicaTransicao(RecursosCinematica *recursos, int fase, EstadoCinematicas *estados){
    if (!estados->inicializadoTransicao){
        estados->narutoXTransicao = 300;
        estados->inicializadoTransicao = true;
    }
    
    UpdateMusicStream(recursos->musicaFundo);
    
    Texture2D terreno;
    float buracoX = 850;
    float buracoY = 240;
    float narutoY = 320;
    
    switch(fase){
        case 1:
            terreno = recursos->faseDragonBallTerreno;
            buracoY = 280;
            narutoY = 360;
            break;
        case 2:
            terreno = recursos->faseOnePieceTerreno;
            buracoY = 240;
            narutoY = 320;
            break;
        case 3:
            terreno = recursos->faseHarryPotterTerreno;
            buracoY = 280;
            narutoY = 360;
            break;
        case 4:
            terreno = recursos->faseResidentEvilTerreno;
            buracoY = 280;
            narutoY = 360;
            break;
        case 5:
            terreno = recursos->faseSilentHillTerreno;
            buracoY = 280;
            narutoY = 360;
            break;
        default:
            return true;
    }
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawTexture(terreno, 0, 0, WHITE);
    
    DrawTexture(recursos->buracoNegro, buracoX, buracoY, WHITE);
    if (estados->narutoXTransicao < 800){
        if (IsKeyDown(KEY_D)){
            DrawTexture(recursos->narutoCorrendo, estados->narutoXTransicao, narutoY, WHITE);
            estados->narutoXTransicao += 8.0f;
        } else{
            DrawTexture(recursos->narutoParado, estados->narutoXTransicao, narutoY, WHITE);
        }
        
        // centraliza o texto no topo
        const char *texto = "Pressione D para correr até o portal!";
        int larguraTexto = MeasureText(texto, 24);
        DrawText(texto, (GetScreenWidth() - larguraTexto) / 2, 30, 24, YELLOW);
    }
    
    // terminou?
    if (estados->narutoXTransicao >= 800){
        estados->inicializadoTransicao = false;
        estados->narutoXTransicao = 300;
        EndDrawing();
        return true;
    }
    
    EndDrawing();
    return false;
}
