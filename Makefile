CC = gcc
SRC_DIR = src

install:	gdc
	cp gdc /usr/local/bin

gdc:	$(SRC_DIR)/main.c
	$(CC) $(SRC_DIR)/main.c -o gdc