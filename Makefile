# Verifica o sistema operacional
ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

BINNAME = hello

ifeq ($(OS),Windows_NT)
	INCLUDE = -I./include/ -L./libwin
	EXTRA_FLAGS = -Wall -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm
	BIN = $(BINNAME).exe
	RM = del /Q /F
else
	INCLUDE=-I./include/ -L./lib
	EXTRA_FLAGS = -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	BIN =./$(BINNAME)
	RM = rm -f
endif

SRC := $(wildcard src/*.c)

all:
	gcc $(SRC) -g $(INCLUDE) -o $(BIN) $(EXTRA_FLAGS)

run:
	$(BIN)

debug:
	gdb $(BIN)

clean:
	$(RM) $(BIN)


valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)

# Helper: build the project on a non-OneDrive drive to avoid "ld: No space left on device"
# Usage: make build_offdrive      (will copy repo to $(BUILD_OFFDRIVE_DIR) and run make there)
BUILD_OFFDRIVE_DIR ?= D:/tmp_build

.PHONY: build_offdrive
build_offdrive:
	@cmd /c "if not exist \"$(BUILD_OFFDRIVE_DIR)\" mkdir \"$(BUILD_OFFDRIVE_DIR)\""
	@cmd /c "robocopy . \"$(BUILD_OFFDRIVE_DIR)\" /E /XD .git .vs /NFL /NDL /NJH /NJS > NUL"
	@cmd /c "cd \"$(BUILD_OFFDRIVE_DIR)\" && make -f Makefile all"