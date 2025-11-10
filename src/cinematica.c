#include "cinematica.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>

bool carregarRecursosCinematica(RecursosCinematica *recursos){
    memset(recursos, 0, sizeof(RecursosCinematica));

    int tamanhoX_N = 150;
    int tamanhoY_N = 150;
    int largura = 1200;
    int altura = 800; 

    if (FileExists("assets/imagens/Terreno/konoha.jpg")){
        Image img = LoadImage("assets/imagens/Terreno/konoha.jpg");
        ImageResize(&img, largura, altura);
        recursos->faseNarutoTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/DragonBall.png")){
        Image img = LoadImage("assets/imagens/Terreno/DragonBall.png");
        ImageResize(&img, largura, altura);
        recursos->faseDragonBallTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/OnePiece.png")){
        Image img = LoadImage("assets/imagens/Terreno/OnePiece.png");
        ImageResize(&img, largura, altura);
        recursos->faseOnePieceTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/Hogwarts.png")){
        Image img = LoadImage("assets/imagens/Terreno/Hogwarts.png");
        ImageResize(&img, largura, altura);
        recursos->faseHarryPotterTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/ResidentEvil.png")){
        Image img = LoadImage("assets/imagens/Terreno/ResidentEvil.png");
        ImageResize(&img, largura, altura);
        recursos->faseResidentEvilTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Terreno/SilentHill.png")){
        Image img = LoadImage("assets/imagens/Terreno/SilentHill.png");
        ImageResize(&img, largura, altura);
        recursos->faseSilentHillTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Terreno/Elimur.png")){
        Image img = LoadImage("assets/imagens/Terreno/Elimur.png");
        ImageResize(&img, largura, altura);
        recursos->faseFinalTerreno = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega sprites do narutinho
    if (FileExists("assets/imagens/Sprite/NarutinhoParado.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutinhoParado.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
        recursos->narutoParado = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutoAndando.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoAndando.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
        recursos->narutoAndando = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Sprite/NarutoAndandoL.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoAndandoL.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
        recursos->narutoAndandoL = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutinhoCorrendo.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutinhoCorrendo.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
        recursos->narutoCorrendo = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Sprite/NarutoCorrendoL.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoCorrendoL.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
        recursos->narutoCorrendoL = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    if (FileExists("assets/imagens/Sprite/NarutoPulando.png")){
        Image img = LoadImage("assets/imagens/Sprite/NarutoPulando.png");
        ImageResize(&img, tamanhoX_N, tamanhoY_N);
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
        ImageResize(&img, 2420, 1440);
        recursos->caixaDialogo = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Sprite/Elimur_Revelado.png")){
        Image img = LoadImage("assets/imagens/Sprite/Elimur_Revelado.png");
        ImageResize(&img, largura / 2, altura - 100);
        recursos->elimurRevelado = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Sprite/Elimur_Mascara.png")){
        Image img = LoadImage("assets/imagens/Sprite/Elimur_Mascara.png");
        ImageResize(&img, largura / 2, altura - 100);
        recursos->elimurMascara = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    if (FileExists("assets/imagens/Sprite/Elimur_TirandoM.png")){
        Image img = LoadImage("assets/imagens/Sprite/Elimur_TirandoM.png");
        ImageResize(&img, largura / 2, altura - 100);
        recursos->elimurTirandoM = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    // carrega buraco negro 
    if (FileExists("assets/imagens/Terreno/BuracoNegro.png")){
        Image img = LoadImage("assets/imagens/Terreno/BuracoNegro.png");
        ImageResize(&img, 350, 350);
        recursos->buracoNegro = LoadTextureFromImage(img);
        UnloadImage(img);
    }
    
    InitAudioDevice();
    // carrega música
    if (FileExists("assets/audio/Select.WAV")){
        recursos->musicaDeselec = LoadMusicStream("assets/audio/Select.WAV");
        SetMusicVolume(recursos->musicaDeselec, 0.2f);
        PlayMusicStream(recursos->musicaDeselec);
    }

    if (FileExists("assets/audio/Select.WAV")){
        recursos->musicaOnePiece = LoadMusicStream("assets/audio/OnePiece.mp3");
        SetMusicVolume(recursos->musicaOnePiece, 0.5f);
        PlayMusicStream(recursos->musicaOnePiece);
    }
    
    recursos->carregado = true;
    return true;
}

void descarregarRecursosCinematica(RecursosCinematica *recursos){
    if (!recursos->carregado) return;
    
    UnloadTexture(recursos->faseNarutoTerreno);
    UnloadTexture(recursos->faseDragonBallTerreno);
    UnloadTexture(recursos->faseOnePieceTerreno);
    UnloadTexture(recursos->faseHarryPotterTerreno);
    UnloadTexture(recursos->faseResidentEvilTerreno);
    UnloadTexture(recursos->faseSilentHillTerreno);
    UnloadTexture(recursos->faseFinalTerreno);
    UnloadTexture(recursos->narutoParado);
    UnloadTexture(recursos->narutoAndando);
    UnloadTexture(recursos->narutoAndandoL);
    UnloadTexture(recursos->narutoCorrendo);
    UnloadTexture(recursos->narutoCorrendoL);
    UnloadTexture(recursos->narutoPulando);
    UnloadTexture(recursos->narutoFalando);
    UnloadTexture(recursos->elimurParado);
    UnloadTexture(recursos->elimurFalando);
    UnloadTexture(recursos->caixaDialogo);
    UnloadTexture(recursos->elimurRevelado);
    UnloadTexture(recursos->elimurMascara);
    UnloadTexture(recursos->elimurTirandoM);
    UnloadTexture(recursos->buracoNegro);
    UnloadMusicStream(recursos->musicaOnePiece);
    UnloadMusicStream(recursos->musicaDeselec);
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

const char* dialogos_fase0[] ={
    "NARRADOR: Elimur, um poderoso vilão de outro universo,|surge com um plano ambicioso: fundir realidades|e conquistar todos os mundos.", 
    "Porém, em uma de suas tentativas de viajar entre os|diferentes universos acaba chegando em Konoha, descobrindo que|controlar a travessia entre", 
    "universos não é tão simples quanto imaginava.|No calor da batalha, Naruto, líder da Vila Oculta da Folha,|une seu chakra natural ao poder avassalador", 
    "da Nove Caudas e em um momento de puro instinto,|acaba rasgando o tecido do espaço-tempo. Sem querer,|ele abre um portal para o Multiverso dos animes e ",
    "jogos — e acaba sendo tragado por ele.|Agora, perdido em mundos desconhecidos e sem controle|sobre o próprio caminho, Naruto precisa encontrar" ,
    "palavras-chave que o ajudem a avançar de universo em universo.|Enquanto busca o caminho de volta para casa, ele também deve", 
    "impedir Elimur de aproveitar a brecha criada e conquistar o multiverso.",
};

const char* dialogos_fase1[] ={
    "NARRADOR: Narutinho se vê preso em lugar totalmente desconhecido|uma energia diferente paira no ar",
    "Narutinho: O que houve?? Onde estou?? Esse chakra… não espera|acho que é Ki?! Será que eu virarei um Sayajin de nove caudas?!",
    "ELIMUR: Agora vou conquistar todos os universos finalmente,|espero que o Narutinho erre esta palavras chave,|para que eu domine este universo.",
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
    "NARRADOR: Depois de escapar (mais ou menos) da escola de magia,|Narutinho dá decara com um lugar... morto demais para estar vivo. |Ruelas escuras, gemidos estranhos e cheiro de laboratório mal higienizado.",
    "Sim, ele caiu em um mundo infestado pelos erros da ciência:|bem-vindo à cidade dos zumbis, bem-vindo à Raccoon City.",
    "Enquanto tenta entender o que é um T-vírus ele percebe que a |palavra-chave pode estar no coração da Umbrella Corporation...",
    "ou no cérebro de algum zumbi esfomeado.",
    "NARUTO: Que tipo de invocação é essa? Esses 'caras' não têm nem|chakra ECA, esse tentou me morder! Clones... com desinfetante, já!",
    "ELIMUR: Eles não correm, mas também não cansam...|perfeito para os meus planos. Se o Valdemort falhou, talvez esses|mortos-vivos consigam deter Narutinho.",
    "JOGO"
};
    
const char* dialogos_fase5[] ={
    "NARRADOR: A névoa desce. O silêncio grita. Narutinho|mal consegue enxergar dois passos à frente — e o que vê...",
    "talvez preferisse não ter visto. Ele entrou em Silent Hill,|um lugar onde os medos ganham forma e os pecados têm rosto.",
    "Aqui, a realidade se retorce e os monstros vêm de dentro.|A chave para sair pode estar escondida nos cantos mais|sombrios da própria alma...",
    "ou atrás daquele espelho que definitivamente não estava ali antes.",
    "NARUTO: Ei... isso é um Genjutsu? Por que minha sombra|está chorando? E quem acendeu essa sirene?! Ah não, de novo não...",
    "ELIMUR: Heh... este lugar sabe explorar os medos. Talvez nem|precise lutar. Que o próprio Narutinho se destrua por dentro.",
    "JOGO"
};

const char* dialogos_fase6[] ={
    "NARRADOR: Após enfrentar mundos de magia, zumbis e horrores psicológicos,|Narutinho chega ao fim de sua jornada multiversal.", 
    "Uma última palavra-chave o separa da verdade —|e talvez, do caminho de volta para casa.|Mas esta não é uma palavra qualquer. Se acertá-la,", 
    "Narutinho não apenas abrirá o portal final...|como também revelará o maior mistério de todos:|quem — ou o que — é Elimur.",
    "Agora, tudo está em jogo. O destino do multiverso...|e a identidade do vilão de nome duvidoso.",
    "NARUTO: Tá... respira, concentra... essa é a última.|Se eu errar, posso ficar preso neste infinito jogo para sempre.|Mas se eu acertar.. “RAMEN!”",
    "ELIMUR: Você nunca irá vencer e nem descobrir quem realmente sou,|afinal estive com você este período todo....",
    "JOGO"
};

bool executarCinematicaIntro(RecursosCinematica *recursos, int fase, EstadoCinematicas *estados){
    if (!estados->estadoIntro.inicializado){
        inicializarCinematica(&estados->estadoIntro, fase);
        estados->estadoIntro.inicializado = true;
    }
    
    // atualiza música
    
    Texture2D terreno;
    const char **dialogos;
    int numeroDialogos;
    float narutoBaseY[6];
    float elimurBaseY[6];
    
    switch(fase){
        case 1:
            terreno = recursos->faseDragonBallTerreno;
            dialogos = dialogos_fase1;
            numeroDialogos = 4;
            narutoBaseY[1] = 380;
            elimurBaseY[1] = 220;
            break;
        case 2:
            UpdateMusicStream(recursos->musicaOnePiece);
            terreno = recursos->faseOnePieceTerreno;
            dialogos = dialogos_fase2;
            numeroDialogos = 5;
            narutoBaseY[2] = 210;
            elimurBaseY[2] = -60;
            break;
        case 3:
            terreno = recursos->faseHarryPotterTerreno;
            dialogos = dialogos_fase3;
            numeroDialogos = 5;
            narutoBaseY[3] = 360;
            elimurBaseY[3] = -10;
            break;
        case 4:
            terreno = recursos->faseResidentEvilTerreno;
            dialogos = dialogos_fase4;
            numeroDialogos = 7;
            narutoBaseY[4] = 570;
            elimurBaseY[4] = 410;
            break;
        case 5:
            terreno = recursos->faseSilentHillTerreno;
            dialogos = dialogos_fase5;
            numeroDialogos = 7;
            narutoBaseY[5] = 450;
            elimurBaseY[5] = 300;
            break;
        case 6:
            terreno = recursos->faseFinalTerreno;
            dialogos = dialogos_fase6;
            numeroDialogos = 7;
            narutoBaseY[6] = 430;
            elimurBaseY[6] = 280;
            break;
        default:
            return true;
    }
    
    // narutinho entrando
    if (estados->estadoIntro.narutoX < 400 && fase != 2){
        estados->estadoIntro.narutoX += 6.0f;
    }

    if (estados->estadoIntro.narutoX > 300 && estados->estadoIntro.narutoX < 400 && fase == 2){
        estados->estadoIntro.narutoX += 2.f;
    }else{ 
        if(fase == 2 && estados->estadoIntro.narutoX <= 400){
            estados->estadoIntro.narutoX += 2.f;
        }
        if (estados->estadoIntro.narutoX > 150 && estados->estadoIntro.narutoX < 300 && fase == 2){
            estados->estadoIntro.narutoX += 1.f;
            estados->estadoIntro.narutoY += 1.8f;
        }
        if(estados->estadoIntro.narutoX >= 400 && fase == 2){}
    }
    
    BeginDrawing();
    ClearBackground(BLACK);
    
    DrawTexture(terreno, 0, 0, WHITE);
    
    for(int i = 1; i < 7; i++){
        if(fase == i){
        DrawTexture(recursos->elimurParado, 850, elimurBaseY[i], WHITE);
        }
    }
    
    for(int i = 1; i < 7; i++){
        if(fase == i){
            if (estados->estadoIntro.narutoX < 400 && fase != 2){
                DrawTexture(recursos->narutoCorrendo, estados->estadoIntro.narutoX - recursos->narutoCorrendo.width, narutoBaseY[i], WHITE);
            } else{
                if(fase != 2){
                    DrawTexture(recursos->narutoParado, estados->estadoIntro.narutoX - recursos->narutoParado.height, narutoBaseY[i], WHITE);
                }
            }
        }
    }
    

    if (estados->estadoIntro.narutoX > 300 && estados->estadoIntro.narutoX < 400 && fase == 2){
        DrawTexture(recursos->narutoCorrendo, estados->estadoIntro.narutoX - recursos->narutoCorrendo.height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
    } else {
        if (fase == 2 && estados->estadoIntro.narutoX <= 150){
            DrawTexture(recursos->narutoCorrendo, estados->estadoIntro.narutoX - recursos->narutoParado.height, narutoBaseY[2], WHITE);
        }
        if (estados->estadoIntro.narutoX > 150 && estados->estadoIntro.narutoX < 300 && fase == 2){
            DrawTexture(recursos->narutoPulando, estados->estadoIntro.narutoX - recursos->narutoParado.height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
        }
        if(estados->estadoIntro.narutoX >= 400 && fase == 2){
            DrawTexture(recursos->narutoParado, estados->estadoIntro.narutoX - recursos->narutoParado.height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
        }
    }

    
    if (estados->estadoIntro.dialogoAtual < numeroDialogos && estados->estadoIntro.narutoX >= 400){
        const char *dialogo = dialogos[estados->estadoIntro.dialogoAtual];
        
        // desenha caixa de diálogo 
        DrawTexture(recursos->caixaDialogo, 0, 172, WHITE);
        
        // identifica quem está falando
        bool narutoFala = (strncmp(dialogo, "NARUTO", 6) == 0 || strncmp(dialogo, "Narutinho", 9) == 0);
        bool elimurFala = (strncmp(dialogo, "ELIMUR", 6) == 0 || strncmp(dialogo, "Elimur", 6) == 0);
        
        // desenha o personagem que está falando 
        if (narutoFala){
            DrawTexture(recursos->narutoFalando, 20, 440, WHITE);
        } else if (elimurFala){
            DrawTexture(recursos->elimurFalando, 880, 440, WHITE);
        }
        
        // desenha o texto do diálogo 
        char buffer[500];
        strcpy(buffer, dialogo);
        int y = 710;
        
        char *linha = strtok(buffer, "|");
        while (linha != NULL && y < GetScreenHeight() - 10){
            DrawText(linha, 40, y, 30, BLACK);
            y += 26;
            linha = strtok(NULL, "|");
        }
        
        if (IsKeyPressed(KEY_ENTER)){
            estados->estadoIntro.dialogoAtual++;
            UpdateMusicStream(recursos->musicaDeselec);
        }
    }
    
    if (estados->estadoIntro.dialogoAtual >= numeroDialogos - 1){
        const char *texto = "Pressione ESPACO para começar o desafio!";
        int larguraTexto = MeasureText(texto, 24);
        DrawText(texto, (GetScreenWidth() - larguraTexto) / 2, 30, 24, YELLOW);
        if(IsKeyPressed(KEY_SPACE) && fase == 1){
            estados->estadoIntro.inicializado = true;
        }
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
        estados->narutoXTransicao = 260;
        estados->inicializadoTransicao = true;
        estados->tempoTransicao = 0.0f;
        estados->Transicao = 0.0f;
    }
    
    Texture2D terreno;
    float buracoX = 850;
    float buracoY[6];
    float narutoY[6];
    float frame = 2.0f;   
    
    switch(fase){
        case 1:
            terreno = recursos->faseDragonBallTerreno;
            buracoY[1] = 280;
            narutoY[1] = 380;
            break;
        case 2:
            terreno = recursos->faseOnePieceTerreno;
            buracoY[2] = 110;
            narutoY[2] = 120;
            break;
        case 3:
            terreno = recursos->faseHarryPotterTerreno;
            buracoY[3] = 280;
            narutoY[3] = 360;
            break;
        case 4:
            terreno = recursos->faseResidentEvilTerreno;
            buracoY[4] = 400;
            narutoY[4] = 570;
            break;
        case 5:
            terreno = recursos->faseSilentHillTerreno;
            buracoY[5] = 320;
            narutoY[5] = 450;
            break;
         case 6:
            terreno = recursos->faseFinalTerreno;
            buracoY[6] = 320;
            narutoY[6] = 430;
            break;
            default:
            return true;
        }

        estados->tempoTransicao += GetFrameTime();

        if(estados->tempoTransicao >= frame) {
            estados->Transicao = (estados->Transicao + 1) % 3;
            estados->tempoTransicao = 0;
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTexture(terreno, 0, 0, WHITE);

        for(int i = 1; i < 7; i++){
            if(fase == i){
                DrawTexture(recursos->buracoNegro, buracoX, buracoY[i], WHITE);
            if(estados->narutoXTransicao < 0){
                estados->narutoXTransicao *= -1.1;
            }
            if (estados->narutoXTransicao < 800){
                if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_A)){
                    estados->narutoXTransicao += 5.0f;
                    if(estados->Transicao == 0){
                        DrawTexture(recursos->narutoAndando, estados->narutoXTransicao, narutoY[i], WHITE);
                    }else{
                        DrawTexture(recursos->narutoParado, estados->narutoXTransicao, narutoY[i], WHITE);
                    }
                } else{
                    if(!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT_SHIFT)){
                        DrawTexture(recursos->narutoParado, estados->narutoXTransicao, narutoY[i], WHITE);
                    }
                }

                if(IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_A)){
                    DrawTexture(recursos->narutoCorrendo, estados->narutoXTransicao, narutoY[i], WHITE);
                    estados->narutoXTransicao += 10.0f;
                }

                if(IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_D)){
                    DrawTexture(recursos->narutoAndandoL,  estados->narutoXTransicao, narutoY[i], WHITE);
                    estados->narutoXTransicao -= 5.0f;
                }

                if(IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_D)){
                    DrawTexture(recursos->narutoCorrendoL,  estados->narutoXTransicao, narutoY[i], WHITE);
                    estados->narutoXTransicao -= 10.0f;
                }

                if(IsKeyDown(KEY_A) && IsKeyDown(KEY_D)){
                    DrawTexture(recursos->narutoParado, estados->narutoXTransicao, narutoY[i], WHITE);
                } 
        
            // centraliza o texto no topo
            const char *texto = "Pressione D para correr até o portal!";
            int larguraTexto = MeasureText(texto, 24);
            DrawText(texto, (GetScreenWidth() - larguraTexto) / 2, 30, 24, YELLOW);
            }

        }
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
