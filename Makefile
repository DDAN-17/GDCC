CC = gcc
SRC_DIR = src

install:	gdc
	cp gdc /usr/local/bin

gdc:	$(SRC_DIR)/main.c $(SRC_DIR)/scanner.c
	$(CC) $(SRC_DIR)/main.c $(SRC_DIR)/scanner.c -o gdc

clean:
	rm gdc