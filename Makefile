CC=cc
BIN=life
FLAG=-g -std=c17 -Wall -Wextra -Werror -pedantic -lraylib

all: comp

comp:
	$(CC) -o $(BIN) $(FLAG) $(BIN).c

exec:
	./$(BIN)
