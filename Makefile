
CC = gcc
CFLAGS = -Wall -O2
SRC = src
BUILD = build

BANNER_OBJ = $(BUILD)/banner.o

all: build encryptor decryptor scanner

build:
	mkdir -p $(BUILD)

encryptor: build $(SRC)/encryptor.c $(BANNER_OBJ)
	$(CC) $(CFLAGS) $(SRC)/encryptor.c $(BANNER_OBJ) -o $(BUILD)/encryptor

decryptor: build $(SRC)/decryptor.c $(BANNER_OBJ)
	$(CC) $(CFLAGS) $(SRC)/decryptor.c $(BANNER_OBJ) -o $(BUILD)/decryptor

scanner: build $(SRC)/scanner.c $(BANNER_OBJ)
	$(CC) $(CFLAGS) $(SRC)/scanner.c $(BANNER_OBJ) -o $(BUILD)/scanner

$(BANNER_OBJ): $(SRC)/banner.c
	$(CC) $(CFLAGS) -c $(SRC)/banner.c -o $(BANNER_OBJ)

clean:
	rm -f $(BUILD)/*