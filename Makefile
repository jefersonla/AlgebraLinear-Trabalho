# Compilador a ser usado
CC=gcc
# Flags para o compilador
CFLAGS= -Wextra -Wno-unused-function -Wno-sign-compare -Wno-empty-translation-unit
# Flags para o Linker
LDFLAGS=
# Nome do executavel
EXECUTABLE=matriz
EXECUTABLE_DEBUG=matriz_debug
# Código fonte principal
MAIN_SRC_FILE=main.c
# Codigos fontes
SOURCES=$(MAIN_SRC_FILE)
# Libs sources
LIBS_SRC=utils/ajuda.c utils/utils.c tipos/matriz.c tipos/vetor.c tipos/lista.c tipos/operacoes_matriz.c entrada.c
# Libs sources headers
LIBS_HEADERS=utils/ajuda.h utils/utils.h tipos/matriz.h tipos/vetor.h tipos/lista.h tipos/operacoes_matriz.h entrada.h
# Comment this to ignore TODO WARNINGS!
TODO_WARN=-Wno-unused-parameter

# Rota padrão
all: main

# Compila o projeto principal
main: algebra
	@printf "Todos os modulos compilados com sucesso.\n"
	@printf "Compilacao terminou sem nenhum problema!\n"

# Compila o projeto principal em modo de debug
debug: algebra-debug
	@printf "Todos os modulos com flag para debug compilados com sucesso\n"
	@printf "Compilação terminou sem nenhum problema!\n"

# Compilação do modulo principal
algebra: $(EXECUTABLE)

# Compilação do modulo principal com debug
algebra-debug: $(EXECUTABLE_DEBUG)

# Executavel com debug habilitado
$(EXECUTABLE_DEBUG): $(LIBS_SRC) $(LIBS_HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) -g $(LIBS_SRC) $(TODO_WARN) $(CFLAGS_PARSER) -D DEBUG_MODE

# Executavel
$(EXECUTABLE): $(LIBS_SRC) $(LIBS_HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LIBS_SRC) $(TODO_WARN) $(CFLAGS_PARSER)

# Realiza os testes nos executaveis
#check: test1 test2 test3

# Limpa o ambiente
clean:
	@printf "Limpando pasta do projeto...\n"
	@\rm -rf $(EXECUTABLE) *.out
