GXX=g++
GXX_ARGS=-O2 -Wall -Wextra

SRC=src
BIN=bin/linux
OBJ=$(BIN)/obj

.PHONY: default
default: all

LIBRARIES=$(OBJ)/assignment2.o

$(OBJ)/assignment2.o: $(SRC)/assignment2.cpp
	$(GXX) $(GXX_ARGS) -o $@ -c $<

$(BIN)/main.out: $(SRC)/main.cpp $(LIBRARIES)
	$(GXX) $(GXX_ARGS) -o $@ $< $(LIBRARIES)

all: $(BIN)/main.out

clean:
	rm -f $(BIN)/*.out
	rm -f $(OBJ)/*.o
