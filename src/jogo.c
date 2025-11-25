#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "jogo.h"

void inicializarJogo(EstadoJogo *estado, Palavra *palavra, int fase){
    memset(estado, 0, sizeof(EstadoJogo));
    estado->palavraAtual = palavra;
    estado->tentativaAtual = 0;
    estado->posEntrada = 0;
    estado->venceu = 0;
    estado->perdeu = 0;
    estado->faseAtual = fase;
    estado->tempoEsgotado = 0;
    
    // fase 6 (Elimur) libera dica automaticamente
    estado->dicaRevelada = (fase == 7) ? 1 : 0;// if/else campacto
    
    // define número máximo de tentativas por fase
    if (fase <= 2){
        estado->maxTentativasPermitidas = maxTentativasFacil; // 5 tentativas
    } else{
        estado->maxTentativasPermitidas = maxTentativasDificil; // 3 tentativas
    }//if
    
    // define o tempo inicial baseado na fase
    if (fase == 7){
        // fase final (Elimur) tem 30 segundos
        estado->tempoInicial = 30.0f;
    } else{
        // fases 1-5: 120s, 110s, 100s, 90s, 80s
        estado->tempoInicial = 120.0f - ((fase - 1) * 10.0f);
    }//if
    estado->tempoRestante = estado->tempoInicial;
    
    // inicializa o teclado
    for (int i = 0; i < 26; i++){
        estado->teclado[i] = letraNaoUsada;
    }//for
    
    // inicializa progresso das fases (primeira fase sempre liberada)
    estado->progressoFases[0] = 1; // Liberada
    for (int i = 2; i < 6; i++){
        estado->progressoFases[i] = 0; // Bloqueada
    }//for
}//inicializarJogo

int adicionarLetra(EstadoJogo *estado, char letra){
    if (estado->venceu || estado->perdeu) return 0;
    if (estado->tentativaAtual >= estado->maxTentativasPermitidas) return 0;

    estado->somError = LoadMusicStream("assets/audio/somErro.mp3");
    SetMusicVolume(estado->somError, 0.2f);
    PlayMusicStream(estado->somError);
    
    letra = toupper(letra);// transformando em maiuscula
    if (letra < 'A' || letra > 'Z') return 0;// verificando se uma letra
    
    // não vai deixar digitar letra que já foi testada e tá errada
    int indiceLetra = letra - 'A';
    if (estado->teclado[indiceLetra] == letraErrada){
        UpdateMusicStream(estado->somError); 
        return 0;
    }//if
    
    // não vai deixar digitar a mesma letra duas vezes
    for (int i = 0; i < estado->posEntrada; i++){
        if (estado->entradaAtual[i] == letra){
            UpdateMusicStream(estado->somError); 
            return 0;
        }//if
    }//for
    

    int tamanhoPalavra = strlen(estado->palavraAtual->palavra);

    if (estado->posEntrada >= tamanhoPalavra) return 0;// retorna a 0 quantos a palavra digitada e = ao tamanho da palavra
    
    estado->entradaAtual[estado->posEntrada] = letra;// colocar a nova na palavra digitada
    estado->posEntrada++;// pasa pra proxima letra
    estado->entradaAtual[estado->posEntrada] = '\0';
    
    return 1;
}//adicionarLetra

int removerLetra(EstadoJogo *estado){
    if (estado->venceu || estado->perdeu) return 0;
    if (estado->posEntrada <= 0) return 0;
    
    estado->posEntrada--;// tira uma letra
    estado->entradaAtual[estado->posEntrada] = '\0';
    
    return 1;
}//removerLetra

EstadoLetra verificarLetra(const char *palavraSecreta, const char *tentativa, int posicao){
    int tamanho = strlen(palavraSecreta);
    char letra = tentativa[posicao];
    
    // verifica se tá na posição correta
    if (palavraSecreta[posicao] == letra) return letraCorreta;
    
    // verifica se a letra existe na palavra
    for (int i = 0; i < tamanho; i++){
        if (palavraSecreta[i] == letra){
            return letraPosicaoErrada;
        }//if
    }//for
    
    return letraErrada;
}//verificarLetra

int fazerTentativa(EstadoJogo *estado){
    if (estado->venceu || estado->perdeu) return 0;
    if (estado->tentativaAtual >= estado->maxTentativasPermitidas) return 0;
    
    int tamanhoPalavra = strlen(estado->palavraAtual->palavra);
    
    // verifica se a entrada tá completa
    if (estado->posEntrada != tamanhoPalavra) return 0; // palavra incompleta
    
    // copia a tentativa
    Tentativa *tent = &estado->tentativas[estado->tentativaAtual];
    strcpy(tent->palavra, estado->entradaAtual);
    tent->tamanho = tamanhoPalavra;
    
    // verifica cada letra
    int todasCorretas = 1;
    for (int i = 0; i < tamanhoPalavra; i++){
        tent->estados[i] = verificarLetra(estado->palavraAtual->palavra, tent->palavra, i);// chamando a funçao
        
        if (tent->estados[i] != letraCorreta){
            todasCorretas = 0;
        }//if
        
        // atualiza o estado do teclado
        int indiceLetra = tent->palavra[i] - 'A';
        if (indiceLetra >= 0 && indiceLetra < 26){
            if (estado->teclado[indiceLetra] < tent->estados[i]){
                estado->teclado[indiceLetra] = tent->estados[i];
            }//if
        }//if
    }//for
    
    // verifica se venceu
    if (todasCorretas){
        estado->venceu = 1;
        // libera próxima fase 
        if (estado->faseAtual < 8 && estado->progressoFases[estado->faseAtual] == 0){
            estado->progressoFases[estado->faseAtual] = 1; // libera próxima    
        }//if
        estado->progressoFases[estado->faseAtual - 1] = 2; // marca como concluída  

    }//if
    
    // avança para próxima tentativa
    estado->tentativaAtual++;
    estado->posEntrada = 0;
    memset(estado->entradaAtual, 0, sizeof(estado->entradaAtual));
    
    // verifica derrota
    if (estado->tentativaAtual >= estado->maxTentativasPermitidas && !estado->venceu){
        estado->perdeu = 1;
    }//if
    
    return 1;
}//fazerTentativa

Palavra* selecionarPalavraAleatoria(Palavra *lista, int total, const char *tema){
    // conta palavras do tema
    int count = 0;
    for (int i = 0; i < total; i++){
        if (strcmp(lista[i].tema, tema) == 0){//conta quando for o mesmo tema
            count++;
        }//if
    }//for
    
    if (count == 0) return NULL;// se nao tiver nenhuma palavra retorna nada
    
    // seleciona aleatoriamente
    int escolhido = rand() % count;
    int atual = 0;
    
    //comparando a palavra escolhida com as paralavra da lista
    for (int i = 0; i < total; i++){
        if (strcmp(lista[i].tema, tema) == 0){
            if (atual == escolhido){
                return &lista[i];// retorna a resposta
            }//if
            atual++;
        }//if
    }//for
    
    return NULL;
}//selecionarPalavraAleatoria

void salvarProgresso(EstadoJogo *estado){
    FILE *arquivo = fopen("progresso.dat", "wb");
    if (arquivo == NULL){
        printf("Erro ao salvar progresso!\n");
        return;
    }//if
    
    fwrite(estado->progressoFases, sizeof(int), 8, arquivo);
    fclose(arquivo);
}//salvarProgresso

void carregarProgresso(EstadoJogo *estado){
    FILE *arquivo = fopen("progresso.dat", "rb");
    if (arquivo == NULL){
        estado->progressoFases[0] = 1;
        for (int i = 1; i < 8; i++){
            estado->progressoFases[i] = 0;
        }//for
        return;
    }//if
    
    fread(estado->progressoFases, sizeof(int), 8, arquivo);
    fclose(arquivo);//fecha o arquivo
}//carregarProgresso

void resetarProgresso(EstadoJogo *estado){
    estado->progressoFases[0] = 1;
    for (int i = 1; i < 8; i++){
        estado->progressoFases[i] = 0;
    }//for
    salvarProgresso(estado);
}//resetarProgresso

void atualizarTempo(EstadoJogo *estado, float deltaTime){
    if (estado->venceu || estado->perdeu || estado->tempoEsgotado) return;
    
    estado->tempoRestante -= deltaTime;
    
    if (estado->tempoRestante <= 0.0f){
        estado->tempoRestante = 0.0f;
        estado->tempoEsgotado = 1;
        estado->perdeu = 1;
    }//if
}//atualizarTempo

void revelarDica(EstadoJogo *estado){
    if (estado->dicaRevelada) return; // já revelada
    if (estado->faseAtual == 7) return; // fase do Elimur é grátis
    
    estado->dicaRevelada = 1;
    
    // aplica punição de 20 segundos
    estado->tempoRestante -= 20.0f;
    if (estado->tempoRestante < 0.0f){
        estado->tempoRestante = 0.0f;
        estado->tempoEsgotado = 1;
        estado->perdeu = 1;
    }//if
}//revelarDica