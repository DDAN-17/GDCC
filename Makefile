CC = clang
SRC_DIR = src

install:	gdc
	cp gdc /usr/local/bin

gdc:	$(SRC_DIR)/main.c $(SRC_DIR)/scanner.c $(SRC_DIR)/ansi.h $(SRC_DIR)/common.h $(SRC_DIR)/config.h $(SRC_DIR)/localization.h $(SRC_DIR)/scanner.h $(SRC_DIR)/trigger.h $(SRC_DIR)/parser.c $(SRC_DIR)/parser.h $(SRC_DIR)/trigger.c $(SRC_DIR)/array.c $(SRC_DIR)/array.h $(SRC_DIR)/table.h $(SRC_DIR)/table.c $(SRC_DIR)/common.c
	$(CC) -g -Wall $(SRC_DIR)/main.c $(SRC_DIR)/scanner.c $(SRC_DIR)/parser.c $(SRC_DIR)/trigger.c $(SRC_DIR)/array.c $(SRC_DIR)/table.c $(SRC_DIR)/common.c -o gdc

clean:
	rm gdc