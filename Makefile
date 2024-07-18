CC = gcc
SRC_DIR = src

install:	gdc
	cp gdc /usr/local/bin

gdc:	$(SRC_DIR)/main.c $(SRC_DIR)/scanner.c $(SRC_DIR)/ansi.h $(SRC_DIR)/common.h $(SRC_DIR)/config.h $(SRC_DIR)/localization.h $(SRC_DIR)/scanner.h $(SRC_DIR)/trigger.h
	$(CC) $(SRC_DIR)/main.c $(SRC_DIR)/scanner.c -o gdc

clean:
	rm gdc