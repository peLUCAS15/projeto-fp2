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
    }
    *lista = temp;
    strcpy((*lista)[*total].palavra, palavra);
    strcpy((*lista)[*total].dica, dica);
    (*lista)[*total].dificuldade = dificuldade;
    strcpy((*lista)[*total].tema, tema);
    (*total)++;
}

void carregarPalavrasIniciais(Palavra **lista, int *total){
    // tenta carregar o csv
    if (carregarPalavrasCSV(lista, total, "assets/palavras.csv")){
        return; // carregou o csv
    }
    
    // Se não der, usa as palavras padrão para carregar
    printf("Carregando palavras padrão ...\n");
    *lista = NULL;
    *total = 0;
    srand((unsigned int)time(NULL));

    // Fase 1 - DRAGON BALL

    adicionarPalavraDireta(lista, total, "GOKU", "Protagonista principal", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "TRUNKS", "Filho de Vegeta", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "TAIYOKEN", "Golpe de luz ofuscante", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "VADOS", "Anjo do Universo 6", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "KI", "Energia vital usada em lutas", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "GOHAN", "Filho de Goku", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "WHIS", "Treinador dos deuses", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "JIREN", "Guerreiro do Torneio do Poder", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "FUSAO", "Técnica que une dois lutadores", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "BRINCO", "Item usado na fusão Potara", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "MASENKO", "Golpe de energia de Gohan", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "DESTRUICAO", "Poder dos deuses Hakaishin", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "DEUS", "Seres superiores no universo", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "ZARBON", "Soldado de Freeza", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "NAMEKUSEI", "Planeta das esferas do dragão", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "BARDOCK", "Pai de Goku", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "BULMA", "Gênio inventora da Corporação Cápsula", 1, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "CONQUISTAR", "Objetivo de muitos vilões", 2, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "WUKONG", "Referência ao Rei Macaco", 3, "Dragon Ball");
    adicionarPalavraDireta(lista, total, "ANJOS", "Assistentes dos deuses da destruição", 3, "Dragon Ball");

    // Fase 2 - ONE PIECE

    adicionarPalavraDireta(lista, total, "ODA", "Criador do mangá One Piece", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "SERAPHIM", "Armas humanas clonadas", 3, "One Piece");
    adicionarPalavraDireta(lista, total, "BARCO", "Principal meio de transporte dos piratas", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "HAKI", "Energia espiritual usada em combate", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "LUGIA", "Tipo de Akuma no Mi elementar", 3, "One Piece");
    adicionarPalavraDireta(lista, total, "JINBE", "Homem-peixe e aliado de Luffy", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "FRUTA", "Concede poderes especiais", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "GARP", "Avô de Luffy", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "MAPA", "Guia das ilhas da Grand Line", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "CHAPEU", "Símbolo do protagonista Luffy", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "RAYLEIGH", "Ex-membro do Roger Pirates", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "ILHA", "Local onde ocorrem as aventuras", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "REI", "Título sonhado por Luffy", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "NAMI", "Navegadora da tripulação", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "ZOAN", "Tipo de fruta que transforma o corpo", 2, "One Piece");
    adicionarPalavraDireta(lista, total, "ZORO", "Espadachim dos Chapéus de Palha", 1, "One Piece");
    adicionarPalavraDireta(lista, total, "ACE", "Irmão de Luffy", 1, "One Piece");

    // Fase 3 - HARRY POTTER

    adicionarPalavraDireta(lista, total, "LUNA", "Amiga excêntrica de Harry", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "SNAPE", "Professor de Poções em Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "LEVIOSA", "Feitiço de levitação", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "CORVINAL", "Casa conhecida pela inteligência", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "BRUXO", "Usuário de magia", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "CASTELO", "Local onde fica Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "DUELO", "Combate entre bruxos", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "VISGO", "Planta mágica usada em poções", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "TRASGO", "Criatura derrotada no primeiro filme", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "RONY", "Melhor amigo de Harry", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "FENIX", "Ave mágica que renasce das cinzas", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "DRACO", "Rival de Harry na Sonserina", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "BECO", "Local de compras dos bruxos", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "TOM", "Nome verdadeiro de Voldemort", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "FLORESTA", "Local sombrio de Hogwarts", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "IMPERIO", "Maldição imperdoável de controle", 3, "Harry Potter");
    adicionarPalavraDireta(lista, total, "LUMOS", "Feitiço de iluminação", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "QUADRIBOL", "Esporte voando em vassouras", 2, "Harry Potter");
    adicionarPalavraDireta(lista, total, "TREM", "Leva os alunos a Hogwarts", 1, "Harry Potter");
    adicionarPalavraDireta(lista, total, "HOGWARTS", "Escola de magia e bruxaria", 1, "Harry Potter");

    // Fase 4 - RESIDENT EVIL

    adicionarPalavraDireta(lista, total, "ZUMBI", "Criatura infectada por vírus", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "VIRUS", "Causa da infecção no jogo", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "ERVA", "Usada para curar ferimentos", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "LEON", "Um dos protagonistas principais", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "CLAIRE", "Irmã de Chris Redfield", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "MUNICAO", "Essencial para sobreviver", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "RIFLE", "Arma de longo alcance", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "PISTOLA", "Arma comum no jogo", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "MIA", "Personagem do Resident Evil 7", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "JOIA", "Usada em enigmas e portas secretas", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "CHRIS", "Um dos heróis da franquia", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "ASHLEY", "Filha do presidente dos EUA", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "ETHAN", "Protagonista de Resident Evil 7 e 8", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "COFRE", "Usado para guardar itens", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "ENIGMA", "Desafio para abrir portas secretas", 3, "Resident Evil");
    adicionarPalavraDireta(lista, total, "SADLER", "Vilão de Resident Evil 4", 3, "Resident Evil");
    adicionarPalavraDireta(lista, total, "GEMAS", "Itens preciosos e colecionáveis", 2, "Resident Evil");
    adicionarPalavraDireta(lista, total, "BAU", "Onde o jogador guarda objetos", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "SPRAY", "Usado para restaurar vida", 1, "Resident Evil");
    adicionarPalavraDireta(lista, total, "MOEDA", "Usada para trocas ou recompensas", 1, "Resident Evil");

    // Fase 5 - SILENT HILL

    adicionarPalavraDireta(lista, total, "NEVOA", "Marca registrada da cidade", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "RADIO", "Emite ruídos quando há monstros", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "CULTO", "Grupo responsável por rituais sombrios", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "MARY", "Esposa desaparecida de James", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "JAMES", "Protagonista do segundo jogo", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "MAPA", "Ajuda a se localizar na neblina", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "TINA", "Personagem que aparece em memórias", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "MASON", "Sobrenome de Harry Mason", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "HENRY", "Protagonista de Silent Hill 4", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "LAGO", "Local central da cidade", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "MOTEL", "Cenário de encontros estranhos", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "GUIA", "Ajuda a compreender o caminho", 1, "Silent Hill");
    adicionarPalavraDireta(lista, total, "PYRAMID", "Monstro com máscara triangular", 3, "Silent Hill");
    adicionarPalavraDireta(lista, total, "HOSPITAL", "Lugar cheio de enfermeiras monstruosas", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "PESADELO", "Realidade distorcida e assustadora", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "VELHO", "Figura que representa o passado", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "DOENCA", "Tema recorrente dos personagens", 2, "Silent Hill");
    adicionarPalavraDireta(lista, total, "SURTO", "Causa de terror psicológico", 3, "Silent Hill");
    adicionarPalavraDireta(lista, total, "LIRIO", "Flor símbolo da cidade", 1, "Silent Hill");

    adicionarPalavraDireta(lista, total, "MURIEL", "Nome", 3, "Final");
}

void liberarPalavras(Palavra *lista){
    if (lista != NULL){
        free(lista);
    }
}

int carregarPalavrasCSV(Palavra **lista, int *total, const char *nomeArquivo){
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo){
        fprintf(stderr, "Aviso: Não foi possível abrir %s. Usando palavras padrão.\n", nomeArquivo);
        return 0;
    }
    
    *lista = NULL;
    *total = 0;
    
    char linha[257];
    int primeiraLinha = 1;
    
    // lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)){
        // Pula o cabeçalho
        if (primeiraLinha){
            primeiraLinha = 0;
            continue;
        }
        
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
    }
    
    fclose(arquivo);
    
    if (*total == 0){
        fprintf(stderr, "Aviso: Nenhuma palavra carregada do CSV. Usando palavras padrão\n");
        return 0;
    }
    
    printf("Carregadas %d palavras do arquivo %s\n", *total, nomeArquivo);
    return 1;
}