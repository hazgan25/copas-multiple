CC=gcc
CFLAGS=-I. -Wall
DEPS=src/headers/fileUtils.h
OBJ=dist/fileUtils.o dist/main.o  

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist dist mkdir dist
    RM = del /Q
else
    MKDIR = mkdir -p dist
    RM = rm -f
endif

.PHONY: all clean create_dir

all: create_dir copasMutiple copasMutipleForTest

create_dir:
	$(MKDIR)

copasMutiple: $(OBJ)
	$(CC) -o dist/copasMutiple.exe $^

copasMutipleForTest: $(OBJ)
	$(CC) -o test/copasMutipleTest.exe $^

dist/main.o: main.c $(DEPS)
	$(CC) -c -o $@ main.c $(CFLAGS)

dist/fileUtils.o: src/utils/fileUtils.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) dist\*.o copasMutiple
