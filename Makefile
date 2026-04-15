# Variáveis de compilação
CC = g++
CFLAGS = -Wall -O3
THREADS_LIB = -pthread
SRC_DIR = src
BIN_DIR = .

# Alvos principais
all: setup seq thr proc aux

# 1. Cria as pastas necessárias antes de tudo
setup:
	mkdir -p matrizes resultados build

# 2. Compila o Sequencial
seq: $(SRC_DIR)/sequencial.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/sequencial.cpp -o $(BIN_DIR)/seq

# 3. Compila as Threads
thr: $(SRC_DIR)/threads.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/threads.cpp -o $(BIN_DIR)/thr $(THREADS_LIB)

# 4. Compila os Processos
proc: $(SRC_DIR)/processos.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/processos.cpp -o $(BIN_DIR)/proc

# 5. Compila o Auxiliar (Gerador de Matrizes)
aux: $(SRC_DIR)/auxiliar.cpp
	$(CC) $(CFLAGS) $(SRC_DIR)/auxiliar.cpp -o $(BIN_DIR)/aux

# Limpa os executáveis e resultados
clean:
	rm -f seq thr proc aux
	rm -rf resultados/*.txt