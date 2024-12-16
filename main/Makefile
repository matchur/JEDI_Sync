# Nome do executável final
EXEC = programa

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -I./utils -I./yoda -I./spec -I./padawans

# Diretórios com os arquivos .c
SRC_DIRS = . ./utils ./yoda ./spec ./padawans

# Busca automaticamente todos os .c nos diretórios listados
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

# Gera os arquivos objeto .o correspondentes
OBJ = $(SRC:.c=.o)

# Regra padrão: compilar tudo
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regras para compilar os .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para recompilar tudo do zero
rebuild: clean all
