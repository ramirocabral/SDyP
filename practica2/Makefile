CC = gcc
CFLAGS = -lpthread
UTILS = ../utils/
FILES = $(UTILS)utils.c ej1.c
BIN_DIR = bin
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=)

all : $(OBJ)

%: %.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $(BIN_DIR)/$@

run: all
	@if [ -z "$(PROGRAM)" ] || [ -z "$(N)" ] || [ -z "$(T)" ]; then \
		echo "usage: make run PROGRAM=<program> N=<value> T=<value>"; \
		echo "example: make run PROGRAM=my_program N=100 T=4"; \
		exit 1; \
	fi
	@$(BIN_DIR)/$(PROGRAM) $(T) $(N)

clean:
	rm -rf $(BIN_DIR)
