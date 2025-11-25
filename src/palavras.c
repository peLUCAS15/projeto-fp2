#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "palavras.h"

void adicionarPalavraDireta(Palavra **lista, int *total, char *palavra, char *dica, int dificuldade, char *tema){
    Palavra *temp = realloc(*lista, (*total + 1) * sizeof(Palavra));
    if (!temp){
        fprintf(stderr, "Erro de alocação de memória!\n");
        return;
    }//if
    *lista = temp;
    strcpy((*lista)[*total].palavra, palavra);
    strcpy((*lista)[*total].dica, dica);
    (*lista)[*total].dificuldade = dificuldade;
    strcpy((*lista)[*total].tema, tema);
    (*total)++;
}//adicionarPalavraDireta

void carregarPalavrasIniciais(Palavra **lista, int *total){
    // tenta carregar o csv
    if (carregarPalavrasCSV(lista, total, "assets/palavras.csv")){
        return; // carregou o csv
    }//if
    
    // Se não der, usa as palavras padrão para carregar
    printf("Carregando palavras padrão ...\n");
    *lista = NULL;
    *total = 0;
    srand((unsigned int)time(NULL));
   
    // Fase 1 - DRAGON BALL 

    adicionarPalavraDireta(lista, total, "Goku", "Protagonista principal", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Trunks", "Filho de Vegeta", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Taiyoken", "Golpe de luz ofuscante", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Vados", "Anjo do Universo 6", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Ki", "Energia vital usada em lutas", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Gohan", "Filho de Goku", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Whis", "Treinador dos deuses", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Jiren", "Guerreiro do Torneio do Poder", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Nuvem", "Transporte voador de Goku", 2, "Dragon Ball"); 
    adicionarPalavraDireta(lista, total, "Brinco", "Item usado na fusão Potara", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Masenko", "Golpe de energia de Gohan", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Poder", "Nível de força de um guerreiro", 3, "Dragon Ball"); 
    adicionarPalavraDireta(lista, total, "Deus", "Seres superiores no universo", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Zarbon", "Soldado de Freeza", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Broly", "Lendário Super Saiyajin", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Bardock", "Pai de Goku", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Bulma", "Gênio inventora da Corporação Cápsula", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Conquistar", "Objetivo de muitos vilões", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Wukong", "Referência ao Rei Macaco", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "Anjos", "Assistentes dos deuses da destruição", 3, "Dragon Ball");

    // Fase 2 - ONE PIECE 

    adicionarPalavraDireta(lista, total, "Oda", "Criador do mangá One Piece", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Seraphim", "Armas humanas clonadas", 3, "One Piece");
    adicionarPalavraDireta(lista, total, "Barco", "Principal meio de transporte dos piratas", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Haki", "Energia espiritual usada em combate", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "Logia", "Tipo de Akuma no Mi elementar", 3, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Jinbe", "Homem-peixe e aliado de Luffy", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Fruta", "Concede poderes especiais", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Garp", "Avô de Luffy", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Mar", "Onde os piratas navegam", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Vinsmok", "Sobrenome do Sanji", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Rayleigh", "Ex-membro do Roger Pirates", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "Ilha", "Local onde ocorrem as aventuras", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Rei", "Título sonhado por Luffy", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "Nami", "Navegadora da tripulação", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "Zoan", "Tipo de fruta que transforma o corpo", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "Sake", "Bebida favorita do espadachim", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Ace", "Irmão de Luffy", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Gomu", "Nome da fruta do protagonista", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Sanji", "Cozinheiro da tripulação", 1, "One Piece"); 
    adicionarPalavraDireta(lista, total, "Nika", "Deus do sol", 2, "One Piece"); 

    // Fase 3 - HARRY POTTER 

    adicionarPalavraDireta(lista, total, "Luna", "Amiga excêntrica de Harry", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Snape", "Professor de Poções em Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Leviosa", "Feitiço de levitação", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Corvinal", "Casa conhecida pela inteligência", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Bruxo", "Usuário de magia", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Castelo", "Local onde fica Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Duelo", "Combate entre bruxos", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Visgo", "Planta mágica usada em poções", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Trasgo", "Criatura derrotada no primeiro filme", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Rony", "Melhor amigo de Harry", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Fenix", "Ave mágica que renasce das cinzas", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Draco", "Rival de Harry na Sonserina", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Beco", "Local de compras dos bruxos", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Tom", "Nome verdadeiro de Voldemort", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Floresta", "Local sombrio de Hogwarts", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Hagrid", "Guarda-caça e guardião das chaves de Hogwarts", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Lumos", "Feitiço de iluminação", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Quadribol", "Esporte voando em vassouras", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Trem", "Leva os alunos a Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "Hogwarts", "Escola de magia e bruxaria", 1, "Harry Potter");

    // Fase 4 - RESIDENT EVIL 

    adicionarPalavraDireta(lista, total, "Zumbi", "Criatura infectada por vírus", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Fuzil", "Arma de fogo longa e potente", 1, "Resident Evil"); 
    adicionarPalavraDireta(lista, total, "Erva", "Usada para curar ferimentos", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Leon", "Um dos protagonistas principais", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Claire", "Irmã de Chris Redfield", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Chave", "Abre portas trancadas", 2, "Resident Evil"); 
    adicionarPalavraDireta(lista, total, "Rifle", "Arma de longo alcance", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Pistola", "Arma comum no jogo", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Mia", "Personagem do Resident Evil 7", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Orbe", "Item esférico usado em puzzles", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Chris", "Um dos heróis da franquia", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Ashley", "Filha do presidente dos EUA", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Ethan", "Protagonista de Resident Evil 7 e 8", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Cofre", "Usado para guardar itens", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Enigma", "Desafio para abrir portas secretas", 3, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Sadler", "Vilão de Resident Evil 4", 3, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Gemas", "Itens preciosos e colecionáveis", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Bau", "Onde o jogador guarda objetos", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Spray", "Usado para restaurar vida", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "Moeda", "Usada para trocas ou recompensas", 1, "Resident Evil");

    // Fase 5 - SILENT HILL

    adicionarPalavraDireta(lista, total, "Nevoa", "Marca registrada da cidade", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Cano", "Uma das primeiras armas brancas", 1, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Culto", "Grupo responsável por rituais sombrios", 2, "Silent Hill");  
    adicionarPalavraDireta(lista, total, "Mary", "Esposa desaparecida de James", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "James", "Protagonista do segundo jogo", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Hotel", "Local icônico de Silent Hill 2", 1, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Lisa", "Enfermeira que aparece no primeiro jogo", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Mason", "Sobrenome do protagonista do SH1", 1, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Henry", "Protagonista de Silent Hill 4", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Lago", "Local central da cidade", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Motel", "Cenário de encontros estranhos", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Guia", "Ajuda a compreender o caminho", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Pyramid", "Monstro com máscara triangular", 3, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Hospital", "Lugar cheio de enfermeiras monstruosas", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Bruma", "Sinônimo da névoa da cidade", 2, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Velho", "Figura que representa o passado", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Dogma", "Crença da ordem sombria", 2, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Surto", "Causa de terror psicológico", 3, "Silent Hill");
    adicionarPalavraDireta(lista, total, "Culpa", "Sentimento central dos protagonistas", 1, "Silent Hill"); 
    adicionarPalavraDireta(lista, total, "Cheryl", "Filha desaparecida de Harry", 2, "Silent Hill"); 

    // FINAL

    adicionarPalavraDireta(lista, total, "Muriel", "Um nome? Um anagrama?", 3, "Final");
}//carregarPalavrasIniciais

void liberarPalavras(Palavra *lista){
    if (lista != NULL){
        free(lista);
    }//if
}//liberarPalavras

int carregarPalavrasCSV(Palavra **lista, int *total, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo){
        fprintf(stderr, "Aviso: Não foi possível abrir %s. Usando palavras padrão.\n", nomeArquivo);
        return 0;
    }//if
    
    *lista = NULL;
    *total = 0;
    
    char linha[256];
    
    // lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)){
        // remove o \n do final
        linha[strcspn(linha, "\r\n")] = 0;
        
        // pula linhas vazias
        if (strlen(linha) == 0) continue;
        
        // csv: palavra,dica,dificuldade,tema
        char palavra[30], dica[100], tema[30];
        int dificuldade;
        
        // encontra as vírgulas
        char *token = strtok(linha, ",");
        if (!token) continue;
        strncpy(palavra, token, sizeof(palavra) - 1);
        palavra[sizeof(palavra) - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(dica, token, sizeof(dica) - 1);
        dica[sizeof(dica) - 1] = '\0';
        
        token = strtok(NULL, ",");
        if (!token) continue;
        dificuldade = atoi(token);
        
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(tema, token, sizeof(tema) - 1);
        tema[sizeof(tema) - 1] = '\0';
        
        // adiciona a palavra à lista
        adicionarPalavraDireta(lista, total, palavra, dica, dificuldade, tema);
    }//while
    
    fclose(arquivo);
    
    if (*total == 0){
        fprintf(stderr, "Aviso: Nenhuma palavra carregada do CSV. Usando palavras padrão\n");
        return 0;
    }//if
    
    printf("Carregadas %d palavras do arquivo %s\n", *total, nomeArquivo);
    return 1;
}//carregarPalavrasCSV

// Função para salvar palavras no CSV
int salvarPalavrasCSV(Palavra *lista, int total, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        fprintf(stderr, "Erro: Não foi possível abrir %s para escrita.\n", nomeArquivo);
        return 0;
    }//if
    
    for (int i = 0; i < total; i++) {
        fprintf(arquivo, "%s,%s,%d,%s\n", 
                lista[i].palavra, lista[i].dica, lista[i].dificuldade, lista[i].tema);
    }//for
    
    fclose(arquivo);
    printf("Arquivo %s salvo com sucesso! (%d palavras)\n", nomeArquivo, total);
    return 1;
}//salvarPalavrasCSV

// Função para buscar uma palavra na lista
int buscarPalavra(Palavra *lista, int total, const char *palavra) {
    for (int i = 0; i < total; i++) {
        if (_stricmp(lista[i].palavra, palavra) == 0) {
            return i; // retorna o índice da palavra encontrada
        }//if
    }//for
    return -1; // palavra não encontrada
}//buscarPalavra

// Função para remover uma palavra da lista
void removerPalavra(Palavra **lista, int *total, int indice) {
    if (indice < 0 || indice >= *total) {
        printf("Índice inválido!\n");
        return;
    }//if
    
    // move todas as palavras após o índice uma posição para trás
    for (int i = indice; i < *total - 1; i++) {
        strcpy((*lista)[i].palavra, (*lista)[i + 1].palavra);
        strcpy((*lista)[i].dica, (*lista)[i + 1].dica);
        (*lista)[i].dificuldade = (*lista)[i + 1].dificuldade;
        strcpy((*lista)[i].tema, (*lista)[i + 1].tema);
    }//for
    
    (*total)--;
    
    // realoca a memória para o novo tamanho
    Palavra *temp = realloc(*lista, (*total) * sizeof(Palavra));
    if (temp != NULL || *total == 0) {
        *lista = temp;
    }//if
}//removerPalavra

// Função para alterar uma palavra existente
void alterarPalavra(Palavra *lista, int total, int indice, char *novaPalavra, char *novaDica, int novaDificuldade, char *novoTema) {
    if (indice < 0 || indice >= total) {
        printf("Índice inválido!\n");
        return;
    }//if
    
    strcpy(lista[indice].palavra, novaPalavra);
    strcpy(lista[indice].dica, novaDica);
    lista[indice].dificuldade = novaDificuldade;
    strcpy(lista[indice].tema, novoTema);
}//alterarPalavra

// Função para listar palavras por tema
void listarPalavrasPorTema(Palavra *lista, int total, const char *tema) {
    printf("\n=== PALAVRAS DO TEMA: %s ===\n", tema);
    int encontradas = 0;
    
    for (int i = 0; i < total; i++) {
        if (_stricmp(lista[i].tema, tema) == 0) {
            printf("%d. %s - %s (Dif: %d)\n", 
                   encontradas + 1, lista[i].palavra, lista[i].dica, lista[i].dificuldade);
            encontradas++;
        }//if
    }//for
    
    if (encontradas == 0) {
        printf("Nenhuma palavra encontrada para o tema '%s'\n", tema);
    } else {
        printf("Total: %d palavras\n", encontradas);
    }//else
}//listarPalavrasPorTema

// Função para listar todas as palavras
void listarTodasPalavras(Palavra *lista, int total) {
    printf("\n=== TODAS AS PALAVRAS ===\n");
    for (int i = 0; i < total; i++) {
        printf("%d. %s - %s (Dif: %d) [%s]\n", 
               i + 1, lista[i].palavra, lista[i].dica, lista[i].dificuldade, lista[i].tema);
    }//for
    printf("Total: %d palavras\n", total);
}//listarTodasPalavras