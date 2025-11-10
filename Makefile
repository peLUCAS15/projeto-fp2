
# detecta o sistema operacional
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

# compilador e flags básicas
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -Isrc

# configurações específicas por plataforma
ifeq ($(DETECTED_OS),Windows)
    # windows
    LDFLAGS = -Llibwin -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET = $(BIN_DIR)/naruto_multiverso.exe
    RM = rmdir /s /q
    MKDIR = if not exist
    MKDIR_CMD = mkdir
    PATH_SEP = \\
    RUN_CMD = .\$(TARGET)
else ifeq ($(DETECTED_OS),Darwin)
    # macos // não consegui testar no meu mac ainda
    LDFLAGS = -Llib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework CoreAudio
    TARGET = $(BIN_DIR)/naruto_multiverso
    RM = rm -rf
    MKDIR = mkdir -p
    MKDIR_CMD = 
    PATH_SEP = /
    RUN_CMD = ./$(TARGET)
else
    # linux
    LDFLAGS = -Llib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    TARGET = $(BIN_DIR)/naruto_multiverso
    RM = rm -rf
    MKDIR = mkdir -p
    MKDIR_CMD = 
    PATH_SEP = /
    RUN_CMD = ./$(TARGET)
endif

# diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# arquivos fonte e objeto
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/palavras.c $(SRC_DIR)/jogo.c $(SRC_DIR)/interface.c $(SRC_DIR)/cinematica.c
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/palavras.o $(OBJ_DIR)/jogo.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/cinematica.o

# regras


# regra padrão
all: directories $(TARGET)
	@echo "Compilacao concluida com sucesso!"
	@echo "Sistema: $(DETECTED_OS)"
	@echo "Execute com: make run"

# cria os diretórios necessários
ifeq ($(DETECTED_OS),Windows)
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p assets/imagens
	@mkdir -p assets/audio
else
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p assets/imagens
	@mkdir -p assets/audio
endif

# compila o executável
$(TARGET): $(OBJECTS)
	@echo "Linkando executavel..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# compila main.c
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c src/palavras.h src/jogo.h src/interface.h src/cinematica.h
	@echo "Compilando main.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

# compila palavras.c
$(OBJ_DIR)/palavras.o: $(SRC_DIR)/palavras.c $(SRC_DIR)/palavras.h
	@echo "Compilando palavras.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/palavras.c -o $(OBJ_DIR)/palavras.o

# Compila jogo.c
$(OBJ_DIR)/jogo.o: $(SRC_DIR)/jogo.c $(SRC_DIR)/jogo.h $(SRC_DIR)/palavras.h
	@echo "Compilando jogo.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/jogo.c -o $(OBJ_DIR)/jogo.o

# compila interface.c
$(OBJ_DIR)/interface.o: $(SRC_DIR)/interface.c $(SRC_DIR)/interface.h $(SRC_DIR)/jogo.h
	@echo "Compilando interface.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/interface.c -o $(OBJ_DIR)/interface.o

# compila cinematica.c
$(OBJ_DIR)/cinematica.o: $(SRC_DIR)/cinematica.c $(SRC_DIR)/cinematica.h
	@echo "Compilando cinematica.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cinematica.c -o $(OBJ_DIR)/cinematica.o

# executa o programa
run: all
	@echo "Executando Wordle Adventures..."
	@$(RUN_CMD)

# limpa arquivos compilados
ifeq ($(DETECTED_OS),Windows)
clean:
	@echo "Limpando arquivos compilados..."
	@if exist "$(OBJ_DIR)" rmdir /s /q "$(OBJ_DIR)"
	@if exist "$(BIN_DIR)" rmdir /s /q "$(BIN_DIR)"
	@echo "Limpeza concluida!"
else
clean:
	@echo "Limpando arquivos compilados..."
	@$(RM) $(OBJ_DIR)
	@$(RM) $(BIN_DIR)
	@echo "Limpeza concluida!"
endif

# recompila tudo 
rebuild: clean all

# informações do projeto
info:
	@echo "=========================================="
	@echo "  NARUTO NO MULTIVERSO - Informacoes"
	@echo "=========================================="
	@echo "Sistema Operacional: $(DETECTED_OS)"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Bibliotecas: Raylib"
	@echo "Arquivos fonte: $(SOURCES)"
	@echo "Executavel: $(TARGET)"
	@echo "=========================================="

# help
help:
	@echo "=========================================="
	@echo "  NARUTO NO MULTIVERSO - Comandos"
	@echo "=========================================="
	@echo "Sistema detectado: $(DETECTED_OS)"
	@echo ""
	@echo "Comandos disponiveis:"
	@echo "  make        - Compila o projeto"
	@echo "  make run    - Compila e executa"
	@echo "  make clean  - Remove arquivos compilados"
	@echo "  make rebuild- Recompila do zero"
	@echo "  make info   - Mostra informacoes do projeto"
	@echo "  make help   - Mostra esta ajuda"
	@echo "=========================================="

.PHONY: all directories run clean rebuild info help