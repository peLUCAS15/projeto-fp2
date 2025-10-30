/*******************************************************************************************
*
*  Para gerenciar uma coleção de perguntas para o jogo, defina uma estrutura Pergunta
contendo, no mínimo: palavra (texto), uma ou mais dicas (texto), nível de dificuldade. O
sistema deverá permitir cadastrar (inserir/ listar/ pesquisar/ alterar/ excluir) as palavras
disponíveis. Essa relação deve aumentar e diminuir dinamicamente.

◦ O mecanismo da sequencia de palavras pode ser escolhido pela equipe. Exemplo:
várias palavras em nível crescente de dificuldade, pontuação, vidas, tempo, etc.

◦ Deverá permitir pesquisar e visualizar as palavras por nível de dificuldade e categoria,
navegando entre elas. Para isso utilize cores, sons e sua criatividade.

◦ Deverá apresentar um menu inicial com as opções disponíveis. Caso necessário,
submenus. A interface deverá ser fácil e intuitiva, seja criativo, utilize cores e beeps :) .
Trate erros do usuário com mensagens e alertas.

◦ A lista com os dados para as palavras iniciais será construída lendo os dados de um
arquivo .csv (valores separados por vírgula) construído pela equipe que deve ser lido e
carregado em um vetor de tamanho dinâmico na primeira abertura do programa. Esse
arquivo deve ter no mínimo 100 palavras

◦ Ao sair do programa, todos os dados devem ser salvos em arquivos binários no HD e
recarregados novamente ao iniciar. Caso os arquivos não existam, eles devem ser
criados e uma mensagem de boas vindas deve ser apresentada ao usuário;

◦ O sistema deverá exibir no menu uma opção de exportar ao dados das questões em um
arquivo texto no formato .CSV (separados por vírgula);
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{

  char palavra[100];
  char dicas[3][200];
  int nivelDificuldade;

} Pergunta;

int main(void){
    
    int i = 0;
    int contador = 0;
    float poxicao_x = 0.f;
    bool correndo = false;
    float poxicao_y = 0.f;
    bool PULANDO = false;

  const int altura = 1200;
  const int largura = 1000;

  InitWindow(altura, largura, "Termo entre dimençoes");//abrindo a janela do jogo
  SetTargetFPS(60);//fps do jogo

  Image fase_1 = LoadImage("Imagens/Terreno/DragonBall.png");//abrindo a imagem
  ImageResize(&fase_1, 1200, 1000);//redimensionado a imagem
  Texture2D textura = LoadTextureFromImage(fase_1);//tranformando a imagem em uma textura
  UnloadImage(fase_1);//fechando a imagem
  
  Image fase_2 = LoadImage("Imagens/Terreno/OnePiece.png");
  ImageResize(&fase_2, 1200, 1000);
  Texture2D textura2 = LoadTextureFromImage(fase_2);
  UnloadImage(fase_2);

  Image fase_3 = LoadImage("Imagens/Terreno/Hogwarts.png");//abrindo a imagem
  ImageResize(&fase_3, 1200, 1000);//redimensionado a imagem
  Texture2D textura3 = LoadTextureFromImage(fase_3);//tranformando a imagem em uma textura
  UnloadImage(fase_3);

  Image fase_4 = LoadImage("Imagens/Terreno/ResidentEvil.png");//abrindo a imagem
  ImageResize(&fase_4, 1200, 1000);//redimensionado a imagem
  Texture2D textura4 = LoadTextureFromImage(fase_4);//tranformando a imagem em uma textura
  UnloadImage(fase_4);

  Image fase_5 = LoadImage("Imagens/Terreno/SilentHill.png");//abrindo a imagem
  ImageResize(&fase_5, 1200, 1000);//redimensionado a imagem
  Texture2D textura5 = LoadTextureFromImage(fase_5);//tranformando a imagem em uma textura
  UnloadImage(fase_5);


  Image naruto = LoadImage("Imagens/Sprite/NarutinhoParado.png");//abrindo a imagem
  ImageResize(&naruto, 150, 150);//redimensionado a imagem
  Texture2D naruto_parado = LoadTextureFromImage(naruto);//tranformando a imagem em uma textura
  UnloadImage(naruto);//fechando a imagem

  Image elimur = LoadImage("Imagens/Sprite/ElimurParado.png");//abrindo a imagem
  ImageResize(&elimur, 300, 300);//redimensionado a imagem
  Texture2D elimur_parado = LoadTextureFromImage(elimur);//tranformando a imagem em uma textura
  UnloadImage(elimur);//fechando a imagem

  Image narutoA = LoadImage("Imagens/Sprite/NarutoAndando.png");//abrindo a imagem
  ImageResize(&narutoA, 150, 150);//redimensionado a imagem
  Texture2D naruto_andando = LoadTextureFromImage(narutoA);//tranformando a imagem em uma textura
  UnloadImage(narutoA);//fechando a imagem

  Image narutoC = LoadImage("Imagens/Sprite/NarutinhoCorrendo.png");//abrindo a imagem
  ImageResize(&narutoC, 150, 150);//redimensionado a imagem
  Texture2D naruto_correndo = LoadTextureFromImage(narutoC);//tranformando a imagem em uma textura
  UnloadImage(narutoC);//fechando a imagem

  Image narutoP = LoadImage("Imagens/Sprite/NarutoPulando.png");//abrindo a imagem
  ImageResize(&narutoP, 150, 150);//redimensionado a imagem
  Texture2D naruto_pulando = LoadTextureFromImage(narutoP);//tranformando a imagem em uma textura
  UnloadImage(narutoP);//fechando a imagem

  Image narutoF = LoadImage("Imagens/Sprite/NarutinhoFalando.png");//abrindo a imagem
  ImageResize(&narutoF, 350, 350);//redimensionado a imagem
  Texture2D naruto_falando = LoadTextureFromImage(narutoF);//tranformando a imagem em uma textura
  UnloadImage(narutoF);//fechando a imagem

  Image elimurF = LoadImage("Imagens/Sprite/ElimurDialogo.png");//abrindo a imagem
  ImageResize(&elimurF, 350, 350);//redimensionado a imagem
  Texture2D elimur_falando = LoadTextureFromImage(elimurF);//tranformando a imagem em uma textura
  UnloadImage(elimurF);//fechando a imagem

  Image caixa = LoadImage("Imagens/Caixas/DialogoNaruto.png");//abrindo a imagem
  ImageResize(&caixa, 2420, 1800);//redimensionado a imagem
  Texture2D caixaDialogo = LoadTextureFromImage(caixa);//tranformando a imagem em uma textura
  UnloadImage(caixa);//fechando a imagem

  Image buracoN = LoadImage("Imagens/Terreno/BuracoNegro.png");//abrindo a imagem
  ImageResize(&buracoN, 500, 500);//redimensionado a imagem
  Texture2D buraco_negro = LoadTextureFromImage(buracoN);//tranformando a imagem em uma textura
  UnloadImage(buracoN);//fechando a imagem

  InitAudioDevice();
  Music mp3 = LoadMusicStream("Audio/BattleTrainerK.ogg");
  PlayMusicStream(mp3);
  
  while(!WindowShouldClose()){//enquanto o usuario nao apertar esc a janela nao se fecha
    
    DrawText("Bem vindo ao jogo", 200, 50, 40, BLACK);
    UpdateMusicStream(mp3);

    BeginDrawing();//desenhando na tela
    ClearBackground(RAYWHITE);//limpando o fundo
    
    switch(i){//controlando as fases
        case 0://fase 1
        DrawTexture(textura, 0, 0, WHITE);//desenhando o fundo da fase 1
        DrawTexture(elimur_parado, 1000, 350, WHITE);//desenhado o vilao
        
        ClearBackground(BLACK);//limpando o fundo
        
        //fazendo o naruto parar quando chegar na posiçao x 300
        if(poxicao_x > 300){DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 500, WHITE);}
        else{
          DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 500, WHITE);//fazer o naruto correr
          poxicao_x += 2.f;
        }
        
        switch(contador){//controlando os dialogos

            case 0:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("NARRADOR: Narutinho se vê preso em lugar totalmente desconhecido", 40, 900, 30, BLACK);
              DrawText("uma energia diferente paira no ar", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER) && poxicao_x > 300){//quando o usuario apertar enter ele troca de dialogo
                contador = 1;
              }//if
            break;

            case 1:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(naruto_falando, -40, 500, WHITE);//desenhando o naruto na tela
              DrawText("Narutinho: O que houve?? Onde estou?? Esse chakra… não espera", 40, 900, 30, BLACK); 
              DrawText("acho que é Ki?! Será que eu virarei um Sayajin de nove caudas?!", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
                contador = 2;
              }//if
            break;

            case 2:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(elimur_falando, 750, 500, WHITE);//desenhado o elimur na tela
              DrawText("Elimur: Agora vou conquistar todos os universos finalmente,", 40, 880, 30, BLACK); 
              DrawText("espero que o Narutinho erre esta palavras chave,", 40, 910, 30, BLACK);
              DrawText("para que eu domine este universo.", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 3;
              }//if
            break;

            case 3:

            if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 4;
            }

            break;
            case 4:

            DrawTexture(textura, 0, 0, WHITE);//desenhando o fundo da fase 1
            DrawTexture(buraco_negro, 800, 350, WHITE);//carregando o buraco negro

            if(IsKeyDown(KEY_D)){//fazendo o personagem andar quando o usuario apertar a tecla D
              correndo = true;//quando o usuario apertar a tecla D "correndo" sera verdade
              poxicao_x += 10.f; 
            }else{correndo = false;}//enqunato o usario nao aperta D "correndo" sera false

            //carrega nuruto correndo quando "correndo" = true
            if(correndo == true){DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 500, WHITE);}//if
            else{DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 500, WHITE);}//carrega naruto parado quando "correndo" = false

            if(poxicao_x > 1000){//quando o naruto chegar no ponto 1000 ele passa de fase
              contador = 0;
              i = 1;
              poxicao_x = 0.f;
            }//if

            break;
          }//switch
        break;

        case 1:
          DrawTexture(textura2, 0, 0, WHITE);//desenhando o fundo da fase 1
          DrawTexture(elimur_parado, 1000, 0, WHITE);//desenhado o vilao
          
          ClearBackground(BLACK);//limpando o fundo
          
          //fazendo o naruto parar quando chegar na posiçao x 300
          if(poxicao_x > 400){
              PULANDO = false;
          }else{
            poxicao_x += 2.f;
            if(poxicao_x > 100){
              PULANDO = true;
              poxicao_y += 1.5f;
              poxicao_x += 2.f;
            }
          }
          
          if(PULANDO == false){
            DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 300 - poxicao_y, WHITE);
          }else{
            DrawTexture(naruto_pulando, poxicao_x - naruto_pulando.width, 300 - poxicao_y, WHITE);
          }

          switch(contador){
            case 0:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("NARRADOR: Narutinho conseguiu encontrar a primeira palavra,", 40, 900, 30, BLACK);
              DrawText("e com isso ele e levado a um novo mundo. Um lugar cercado por mar", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER) && poxicao_x > 300){//quando o usuario apertar enter ele troca de dialogo
                contador = 1;
              }//if
              break;
            case 1:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("e criaturas nunca vistas. As frutas do diabo dominam o lugar,", 40, 900, 30, BLACK);
              DrawText("e uma era de Pirataria deixam as coisas mais perigosoas para ele.", 40, 930, 30, BLACK);

              if(IsKeyPressed(KEY_ENTER)){
                contador = 2;
              }
            break;

            case 2:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(naruto_falando, -40, 500, WHITE);//desenhando o naruto na tela
              DrawText("NARUTO: Gomu Gomu No Rasengan, não pera pera pera.", 40, 880, 30, BLACK); 
              DrawText("Agora sou o pirata mais forte do mundo. Irei desafiar o", 40, 910, 30, BLACK);
              DrawText("Barba Negra, a Marinha e por fim acabar com você Elimur.", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
                contador = 3;
              }//if
            break;

            case 3:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(elimur_falando, 750, 500, WHITE);//desenhado o elimur na tela
              DrawText("ELIMUR: Você conseguiu acertar a palavra anterior,", 40, 880, 30, BLACK); 
              DrawText("mas esta não há fruta do diabo que ira te ajude.", 40, 910, 30, BLACK);
              DrawText("Ninja ou Pirata, nenhum irá garantir sua vitória.", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 4;
              }//if
            break;

            case 4:
             if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 5;
              }//if
            break;

            case 5:
              DrawTexture(textura2, 0, 0, WHITE);//desenhando o fundo da fase 1
              DrawTexture(buraco_negro, 700, -50, WHITE);//carregando o buraco negro

              if(IsKeyDown(KEY_D)){//fazendo o personagem andar quando o usuario apertar a tecla D
                correndo = true;//quando o usuario apertar a tecla D "correndo" sera verdade
                poxicao_x += 10.f; 
              }else{correndo = false;}//enqunato o usario nao aperta D "correndo" sera false

              if(poxicao_x > 600 && poxicao_y > 200){
                poxicao_y -= 10.5f;
              }
              //carrega nuruto correndo quando "correndo" = true
              if(correndo == true){DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 300 - poxicao_y, WHITE);}//if
              else{DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 300 - poxicao_y, WHITE);}//carrega naruto parado quando "correndo" = false

              if(poxicao_x > 1000 && poxicao_y > 100){//quando o naruto chegar no ponto 1000 ele passa de fase
                contador = 0;
                i = 2;
                poxicao_x = 0.f;
              }//if
            break;
          }
        break;

        case 2:
          DrawTexture(textura3, 0, 0, WHITE);//desenhando o fundo da fase 1
          DrawTexture(elimur_parado, 1000, 350, WHITE);//desenhado o vilao
          
          ClearBackground(BLACK);//limpando o fundo

          if(poxicao_x > 300){DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 500, WHITE);}
          else{
          DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 500, WHITE);//fazer o naruto correr
          poxicao_x += 2.f;
          }

          switch(contador){
            case 0:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("NARRADOR: Mesmo conseguindo decifrar mais uma palavra,", 40, 880, 30, BLACK); 
              DrawText("Narutinho se vê preso em um mundo de magia agora", 40, 910, 30, BLACK);
              DrawText("ele, terá que enfrentar um mal que não deve ser nomeado,", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER) && poxicao_x > 300){//quando o usuario apertar enter ele troca de dialogo
                contador = 1;
              }//if
            break;

            case 1:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("e impedir Elimur de fazer um pacto com esse novo ser.", 40, 900, 30, BLACK);
              DrawText("Pois quando dois Mal distinto se une, coisa boa não deve acontecer", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){//quando o usuario apertar enter ele troca de dialogo
                contador = 2;
              }//if
            break;
            
            case 2:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(naruto_falando, -40, 500, WHITE);//desenhando o naruto na tela
              DrawText("NARUTO: Pela minha varinha, lá ele,  e agora, onde estou????", 40, 900, 30, BLACK); 
              DrawText("multiplos clones das sombras.... Será ilusão ou mágia???", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
                contador = 3;
              }//if
            break;
              
            case 3:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(elimur_falando, 750, 500, WHITE);//desenhado o elimur na tela
              DrawText("ELIMUR: Não estou gostando deste desfecho, acho que preciso", 40, 880, 30, BLACK); 
              DrawText("me juntar a Valdemort para conquistar meus objetivos. Quem sabe", 40, 910, 30, BLACK);
              DrawText("um Avada Kedavra no Narutinho dê um jeito em tudo isso", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 4;
              }//if
            break;

            case 4: 
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 5;
              }//if
            break;

            case 5:
              DrawTexture(textura3, 0, 0, WHITE);//desenhando o fundo da fase 1
              DrawTexture(buraco_negro, 800, 350, WHITE);//carregando o buraco negro

              if(IsKeyDown(KEY_D)){//fazendo o personagem andar quando o usuario apertar a tecla D
                correndo = true;//quando o usuario apertar a tecla D "correndo" sera verdade
                poxicao_x += 10.f; 
              }else{correndo = false;}//enqunato o usario nao aperta D "correndo" sera false

              //carrega nuruto correndo quando "correndo" = true
              if(correndo == true){DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 500, WHITE);}//if
              else{DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 500, WHITE);}//carrega naruto parado quando "correndo" = false

              if(poxicao_x > 1000){//quando o naruto chegar no ponto 1000 ele passa de fase
                contador = 0;
                i = 3;
                poxicao_x = 0.f;
              }//if

            break;
          }
        break;

        case 3:
          DrawTexture(textura4, 0, 0, WHITE);//desenhando o fundo da fase 1
          DrawTexture(elimur_parado, 1000, 600, WHITE);//desenhado o vilao
          
          ClearBackground(BLACK);//limpando o fundo

          if(poxicao_x > 300){DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 750, WHITE);}
          else{
          DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 750, WHITE);//fazer o naruto correr
          poxicao_x += 2.f;
          }

          switch(contador){
            case 0:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("Depois de escapar (mais ou menos) da escola de magia, Narutinho dá de", 40, 880, 30, BLACK); 
              DrawText("cara com um lugar... morto demais para estar vivo. Ruelas escuras, gemidos", 40, 910, 30, BLACK);
              DrawText("estranhos e cheiro de laboratório mal higienizado. Sim, ele caiu em", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER) && poxicao_x > 300){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 1;
              }//if
            break;

            case 1:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("um mundo infestado pelos erros da ciência: bem-vindo à cidade dos", 40, 870, 30, BLACK); 
              DrawText("zumbis, bem-vindo à Raccoon City. Enquanto tenta entender o que é um", 40, 900, 30, BLACK);
              DrawText("T-vírus ele percebe que a palavra-chave pode estar no coração da", 40, 930, 30, BLACK);
              DrawText("Umbrella Corporation... ou no cérebro de algum zumbi esfomeado. ", 40, 960, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 2;
              }
            break;

            case 2:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(naruto_falando, -40, 500, WHITE);//desenhando o naruto na tela
              DrawText("NARUTO: Que tipo de invocação é essa? Esses 'caras' não têm nem", 40, 900, 30, BLACK); 
              DrawText("chakra ECA, esse tentou me morder! Clones... com desinfetante, já!", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 3;
              }
            break;

            case 3:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(elimur_falando, 750, 500, WHITE);//desenhado o elimur na tela
              DrawText("ELIMUR: Eles não correm, mas também não cansam...", 40, 880, 30, BLACK); 
              DrawText("perfeito para os meus planos. Se o Valdemort falhou, talvez esses", 40, 910, 30, BLACK);
              DrawText("mortos-vivos consigam deter Narutinho.", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 4;
              }
            break;
            
            case 4:
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
                contador = 5;
              }
            break;

            case 5:
              DrawTexture(textura4, 0, 0, WHITE);//desenhando o fundo da fase 1
              DrawTexture(buraco_negro, 800, 500, WHITE);//carregando o buraco negro

              if(IsKeyDown(KEY_D)){//fazendo o personagem andar quando o usuario apertar a tecla D
                correndo = true;//quando o usuario apertar a tecla D "correndo" sera verdade
                poxicao_x += 10.f; 
              }else{correndo = false;}//enqunato o usario nao aperta D "correndo" sera false

              //carrega nuruto correndo quando "correndo" = true
              if(correndo == true){DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 750, WHITE);}//if
              else{DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 750, WHITE);}//carrega naruto parado quando "correndo" = false

              if(poxicao_x > 1000){//quando o naruto chegar no ponto 1000 ele passa de fase
                contador = 0;
                i = 4;
                poxicao_x = 0.f;
              }//if
              break;
            }
        break;

        case 4:
            DrawTexture(textura5, 0, 0, WHITE);//desenhando o fundo da fase 1
            DrawTexture(elimur_parado, 800, 450, WHITE);//desenhado o vilao
            
            ClearBackground(BLACK);//limpando o fundo

            if(poxicao_x > 300){DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 600, WHITE);}
            else{
            DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 600, WHITE);//fazer o naruto correr
            poxicao_x += 2.f;
            }

          switch(contador){
            case 0:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("NARRADOR: A névoa desce. O silêncio grita. Narutinho", 40, 870, 30, BLACK); 
              DrawText("mal consegue enxergar dois passos à frente — e o que vê...", 40, 900, 30, BLACK);
              DrawText(" talvez preferisse não ter visto. Ele entrou em Silent Hill,", 40, 930, 30, BLACK);
              DrawText("um lugar onde os medos ganham forma e os pecados têm rosto.", 40, 960, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER) && poxicao_x > 300){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 1;
              }//if
            break;
            
            case 1:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawText("Aqui, a realidade se retorce e os monstros vêm de dentro. A chave", 40, 880, 30, BLACK); 
              DrawText("para sair pode estar escondida nos cantos mais sombrios da própria alma...", 40, 910, 30, BLACK);
              DrawText("ou atrás daquele espelho que definitivamente não estava ali antes.", 40, 940, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 2;
              }//if
            break;

            case 2:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(naruto_falando, -40, 500, WHITE);//desenhando o naruto na tela
              DrawText("NARUTO: Ei... isso é um Genjutsu? Por que minha sombra", 40, 900, 30, BLACK); 
              DrawText("está chorando? E quem acendeu essa sirene?! Ah não, de novo não...", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 3;
              }//if
            break;

            case 3:
              DrawTexture(caixaDialogo, 0, 215, WHITE);//desenhado a faixa de dialogo
              DrawTexture(elimur_falando, 750, 500, WHITE);//desenhado o elimur na tela
              DrawText("ELIMUR: Heh... este lugar sabe explorar os medos. Talvez nem", 40, 900, 30, BLACK); 
              DrawText("precise lutar. Que o próprio Narutinho se destrua por dentro.", 40, 930, 30, BLACK);
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 4;
              }//if
            break;

            case 4:
              if(IsKeyPressed(KEY_ENTER)){ //quando o usuario apertar enter ele troca de dialogo 
              contador = 5;
              }//if
            break; 

            case 5:
              DrawTexture(textura5, 0, 0, WHITE);//desenhando o fundo da fase 1
              DrawTexture(buraco_negro, 800, 350, WHITE);//carregando o buraco negro

              if(IsKeyDown(KEY_D)){//fazendo o personagem andar quando o usuario apertar a tecla D
                correndo = true;//quando o usuario apertar a tecla D "correndo" sera verdade
                poxicao_x += 10.f; 
              }else{correndo = false;}//enqunato o usario nao aperta D "correndo" sera false

              //carrega nuruto correndo quando "correndo" = true
              if(correndo == true){DrawTexture(naruto_correndo, poxicao_x - naruto_correndo.width, 600, WHITE);}//if
              else{DrawTexture(naruto_parado, poxicao_x - naruto_parado.width, 600, WHITE);}//carrega naruto parado quando "correndo" = false

              if(poxicao_x > 1000){//quando o naruto chegar no ponto 1000 ele passa de fase
                contador = 0;
                i = 0;
                poxicao_x = 0.f;
              }//if
              break;
            }
          break;   
        }//shitch
      EndDrawing();
  }//while

    UnloadTexture(textura);
    UnloadTexture(textura2);
    UnloadTexture(textura3);
    UnloadTexture(textura4);
    UnloadTexture(textura5);
    UnloadTexture(naruto_andando);
    UnloadTexture(naruto_correndo);
    UnloadTexture(naruto_parado);
    UnloadMusicStream(mp3);
    CloseAudioDevice();
    CloseWindow();

  return 0;
  }//main




  