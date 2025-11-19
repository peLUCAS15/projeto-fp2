#include "cinematica.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

bool carregarRecursosCinematica(RecursosCinematica *recursos){
    memset(recursos, 0, sizeof(RecursosCinematica));

    int tamanhoX_P = 150; int tamanhoY_P = 150;
    int largura = 1200; int altura = 800;
    char terrenos[15][100];
    char sprite[12][100];
    char musica[7][100];
    float volume = 0.5f;
    int i;

    strcpy(terrenos[0],"assets/imagens/Terreno/konoha.jpg");
    strcpy(terrenos[1],"assets/imagens/Terreno/DragonBall.png");
    strcpy(terrenos[2],"assets/imagens/Terreno/OnePiece.png");
    strcpy(terrenos[3],"assets/imagens/Terreno/Hogwarts.png");
    strcpy(terrenos[4],"assets/imagens/Terreno/ResidentEvil.png");
    strcpy(terrenos[5],"assets/imagens/Terreno/SilentHill.png");
    strcpy(terrenos[6],"assets/imagens/Terreno/Elimur.png");
    strcpy(terrenos[7],"assets/imagens/Caixas/DialogoNaruto.png");
    strcpy(terrenos[8],"assets/imagens/Terreno/BuracoNegro.png");
    strcpy(terrenos[9],"assets/imagens/Terreno/FinalExplosao1.png");
    strcpy(terrenos[10],"assets/imagens/Terreno/FinalExplosao2.png");
    strcpy(terrenos[11],"assets/imagens/Terreno/FinalExplosao3.png");
    strcpy(terrenos[12],"assets/imagens/Terreno/FinalExplosao4.png");
    strcpy(terrenos[13],"assets/imagens/Terreno/AntesDFim.png");
    strcpy(terrenos[14],"assets/imagens/Terreno/Final.png");

    strcpy(sprite[0],"assets/imagens/Sprite/NarutinhoParado.png");
    strcpy(sprite[1],"assets/imagens/Sprite/NarutoAndando.png");
    strcpy(sprite[2],"assets/imagens/Sprite/NarutoAndandoL.png");
    strcpy(sprite[3],"assets/imagens/Sprite/NarutinhoCorrendo.png");
    strcpy(sprite[4],"assets/imagens/Sprite/NarutoCorrendoL.png");
    strcpy(sprite[5],"assets/imagens/Sprite/NarutoPulando.png");
    strcpy(sprite[6],"assets/imagens/Sprite/ElimurParado.png");
    strcpy(sprite[7],"assets/imagens/Sprite/NarutinhoFalando.png");
    strcpy(sprite[8],"assets/imagens/Sprite/ElimurDialogo.png");
    strcpy(sprite[9],"assets/imagens/Sprite/Elimur_Revelado.png");
    strcpy(sprite[10],"assets/imagens/Sprite/Elimur_Mascara.png");
    strcpy(sprite[11],"assets/imagens/Sprite/Elimur_TirandoM.png");

    strcpy(musica[0],"assets/audio/Select.WAV");
    strcpy(musica[1],"assets/audio/Naruto.mp3");
    strcpy(musica[2],"assets/audio/DragonBall.mp3");
    strcpy(musica[3],"assets/audio/OnePiece.mp3");
    strcpy(musica[4],"assets/audio/HarryPotter.mp3");
    strcpy(musica[5],"assets/audio/ResidentEvil.mp3");
    strcpy(musica[6],"assets/audio/SilentHill.mp3");


    for(i = 0; i < 15; i++){
        if(strcmp(terrenos[i], "assets/imagens/Caixas/DialogoNaruto.png") == 0){
            largura = 2420; altura = 1440;
        }

        if(strcmp(terrenos[i], "assets/imagens/Terreno/BuracoNegro.png") == 0){
            largura = 350; altura = 350;
        }

        if(strcmp(terrenos[i], "assets/imagens/Terreno/FinalExplosao1.png") == 0){
            largura = 1200; altura = 800;
        }

        if (FileExists(terrenos[i])){
            Image img = LoadImage(terrenos[i]);
            ImageResize(&img, largura, altura);
            recursos->fases[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    }

    // carrega sprites do narutinho
    for(i = 0; i < 12; i++){
        if(strcmp(sprite[i], "assets/imagens/Sprite/ElimurParado.png") == 0){
            tamanhoX_P = 300; tamanhoY_P = 300;
        }
        
        if(strcmp(sprite[i], "assets/imagens/Sprite/NarutinhoFalando.png") == 0 || strcmp(sprite[i], "assets/imagens/Sprite/ElimurDialogo.png") == 0){
            tamanhoX_P = 240; tamanhoY_P = 240;
        }

        if(strcmp(sprite[i], "assets/imagens/Sprite/Elimur_Mascara.png") == 0 || strcmp(sprite[i], "assets/imagens/Sprite/Elimur_Revelado.png") == 0 || 
        strcmp(sprite[i], "assets/imagens/Sprite/Elimur_TirandoM.png") == 0){
            tamanhoX_P = largura / 2; tamanhoY_P = altura - 100;
        }

        if (FileExists(sprite[i])){
            Image img = LoadImage(sprite[i]);
            ImageResize(&img, tamanhoX_P, tamanhoY_P);
            recursos->sprites[i] = LoadTextureFromImage(img);
            UnloadImage(img);
        }
    } 

    InitAudioDevice();
    // carrega música
    for(i = 0; i < 7; i++){
        if(strcmp(musica[i], "assets/audio/Select.WAV") == 0){
            volume = 0.2f;
        }

        if (FileExists(musica[i])){
            recursos->trilhaSonora[i] = LoadMusicStream(musica[i]);
            SetMusicVolume(recursos->trilhaSonora[i], volume);
            PlayMusicStream(recursos->trilhaSonora[i]);
        }
    }


    recursos->carregado = true;
    return true;
}

void descarregarRecursosCinematica(RecursosCinematica *recursos){
    if (!recursos->carregado) return;
    
    for(int i = 0; i < 15; i++){
        UnloadTexture(recursos->fases[i]);
        UnloadTexture(recursos->sprites[i]);
        UnloadMusicStream(recursos->trilhaSonora[i]);
    }
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
    int i;

    for(i = 1; i < 7; i++){
        if(fase == i){
            UpdateMusicStream(recursos->trilhaSonora[i+1]);
        }
    }
    
    switch(fase){
        case 1:
            terreno = recursos->fases[1];
            dialogos = dialogos_fase1;
            numeroDialogos = 4;
            narutoBaseY[1] = 380;
            elimurBaseY[1] = 220;
            break;
        case 2:
            terreno = recursos->fases[2];
            dialogos = dialogos_fase2;
            numeroDialogos = 5;
            narutoBaseY[2] = 210;
            elimurBaseY[2] = -60;
            break;
        case 3:
            terreno = recursos->fases[3];
            dialogos = dialogos_fase3;
            numeroDialogos = 5;
            narutoBaseY[3] = 360;
            elimurBaseY[3] = -10;
            break;
        case 4:
            terreno = recursos->fases[4];
            dialogos = dialogos_fase4;
            numeroDialogos = 7;
            narutoBaseY[4] = 570;
            elimurBaseY[4] = 410;
            break;
        case 5:
            terreno = recursos->fases[5];
            dialogos = dialogos_fase5;
            numeroDialogos = 7;
            narutoBaseY[5] = 450;
            elimurBaseY[5] = 300;
            break;
        case 6:
            terreno = recursos->fases[6];
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
        DrawTexture(recursos->sprites[6], 850, elimurBaseY[i], WHITE);
        }
    }
    
    for(int i = 1; i < 7; i++){
        if(fase == i){
            if (estados->estadoIntro.narutoX < 400 && fase != 2){
                DrawTexture(recursos->sprites[3], estados->estadoIntro.narutoX - recursos->sprites[3].width, narutoBaseY[i], WHITE);
            } else{
                if(fase != 2){
                    DrawTexture(recursos->sprites[0], estados->estadoIntro.narutoX - recursos->sprites[0].height, narutoBaseY[i], WHITE);
                }
            }
        }
    }
    

    if (estados->estadoIntro.narutoX > 300 && estados->estadoIntro.narutoX < 400 && fase == 2){
        DrawTexture(recursos->sprites[3], estados->estadoIntro.narutoX - recursos->sprites[3].height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
    } else {
        if (fase == 2 && estados->estadoIntro.narutoX <= 150){
            DrawTexture(recursos->sprites[3], estados->estadoIntro.narutoX - recursos->sprites[3].height, narutoBaseY[2], WHITE);
        }
        if (estados->estadoIntro.narutoX > 150 && estados->estadoIntro.narutoX < 300 && fase == 2){
            DrawTexture(recursos->sprites[5], estados->estadoIntro.narutoX - recursos->sprites[5].height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
        }
        if(estados->estadoIntro.narutoX >= 400 && fase == 2){
            DrawTexture(recursos->sprites[0], estados->estadoIntro.narutoX - recursos->sprites[0].height, narutoBaseY[2] - estados->estadoIntro.narutoY, WHITE);
        }
    }

    
    if (estados->estadoIntro.dialogoAtual < numeroDialogos && estados->estadoIntro.narutoX >= 400){
        const char *dialogo = dialogos[estados->estadoIntro.dialogoAtual];
        
        // desenha caixa de diálogo 
        DrawTexture(recursos->fases[7], 0, 172, WHITE);
        
        // identifica quem está falando
        bool narutoFala = (strncmp(dialogo, "NARUTO", 6) == 0 || strncmp(dialogo, "Narutinho", 9) == 0);
        bool elimurFala = (strncmp(dialogo, "ELIMUR", 6) == 0 || strncmp(dialogo, "Elimur", 6) == 0);
        
        // desenha o personagem que está falando 
        if (narutoFala){
            DrawTexture(recursos->sprites[7], 20, 440, WHITE);
        } else if (elimurFala){
            DrawTexture(recursos->sprites[8], 880, 440, WHITE);
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
            UpdateMusicStream(recursos->trilhaSonora[0]);
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
    }
    
    Texture2D terreno;
    float buracoX = 850;
    float buracoY[6];
    float narutoY[6];
    float cenaFinal = 1.0f;

    estados->tempoFinal += GetFrameTime();
        
        if(estados->tempoFinal >= cenaFinal) {
            if(estados->tempoFinal < 8) estados->final++;
            estados->tempoFinal = 0;
        }
        if(estados->final == 8) fase = 7;
    
    switch(fase){
        case 1:
            UpdateMusicStream(recursos->trilhaSonora[2]);
            terreno = recursos->fases[1];
            buracoY[1] = 280;
            narutoY[1] = 380;
            break;
        case 2:
            UpdateMusicStream(recursos->trilhaSonora[3]);
            terreno = recursos->fases[2];
            buracoY[2] = 110;
            narutoY[2] = 120;
            break;
        case 3:
            UpdateMusicStream(recursos->trilhaSonora[4]);
            terreno = recursos->fases[3];
            buracoY[3] = 280;
            narutoY[3] = 360;
            break;
        case 4:
            UpdateMusicStream(recursos->trilhaSonora[5]);
            terreno = recursos->fases[4];
            buracoY[4] = 400;
            narutoY[4] = 570;
            break;
        case 5:
            UpdateMusicStream(recursos->trilhaSonora[6]);
            terreno = recursos->fases[5];
            buracoY[5] = 320;
            narutoY[5] = 450;
            break;
        case 6:
            terreno = recursos->fases[6];
            buracoY[6] = 320;
            narutoY[6] = 430;
            break;
        case 7:
            terreno = recursos->fases[14];
            break;
        default:
            return true;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTexture(terreno, 0, 0, WHITE);
        
        for(int i = 1; i < 7; i++){
            if(fase == 6){
                switch(estados->final){
                    case 0: DrawTexture(recursos->sprites[10], 300, 100, WHITE); break;
                    case 1: DrawTexture(recursos->sprites[11], 300, 100, WHITE); break;
                    case 2: DrawTexture(recursos->sprites[9], 300, 100, WHITE); break;
                    case 3: DrawTexture(recursos->fases[9], 0, 0, WHITE); break;
                    case 4: DrawTexture(recursos->fases[10], 0, 0, WHITE); break;
                    case 5: DrawTexture(recursos->fases[11], 0, 0, WHITE); break;
                    case 6: DrawTexture(recursos->fases[12], 0, 0, WHITE); break;
                    case 7: DrawTexture(recursos->fases[13], 0, 0, WHITE); break;
                    case 8: DrawTexture(recursos->fases[14], 0, 0, WHITE); break;
                } 
            }

            if(fase == i && fase != 6){
                DrawTexture(recursos->fases[8], buracoX, buracoY[i], WHITE);
                if(estados->narutoXTransicao < 0) estados->narutoXTransicao *= -1.1;

                if (estados->narutoXTransicao < 800){
                    if (IsKeyDown(KEY_D) && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_A)){
                        estados->narutoXTransicao += 5.0f;
                        if (estados->final == 0) DrawTexture(recursos->sprites[1], estados->narutoXTransicao, narutoY[i], WHITE);
                        else DrawTexture(recursos->sprites[0], estados->narutoXTransicao, narutoY[i], WHITE);
                    } else{
                        if(!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT_SHIFT)) DrawTexture(recursos->sprites[0], estados->narutoXTransicao, narutoY[i], WHITE);
                    }

                    
                    if(IsKeyDown(KEY_D) && IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_A)){
                        DrawTexture(recursos->sprites[3], estados->narutoXTransicao, narutoY[i], WHITE);
                        estados->narutoXTransicao += 10.0f;
                    }
                    
                    if(IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_D)){
                        DrawTexture(recursos->sprites[2],  estados->narutoXTransicao, narutoY[i], WHITE);
                        estados->narutoXTransicao -= 5.0f;
                    }

                    if(IsKeyDown(KEY_A) && IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_D)){
                        DrawTexture(recursos->sprites[4],  estados->narutoXTransicao, narutoY[i], WHITE);
                        estados->narutoXTransicao -= 10.0f;
                    }
                    
                    if(IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) DrawTexture(recursos->sprites[0], estados->narutoXTransicao, narutoY[i], WHITE);
                    if(IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) DrawTexture(recursos->sprites[0], estados->narutoXTransicao, narutoY[i], WHITE); 

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