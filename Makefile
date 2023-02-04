# Compiler
CC := g++

# Headerfiles and Compiler Flags
INCLUDE = -I ./src/include
CFLAGS = -Wextra -std=c++11 -m64 -O3 -c ${INCLUDE}

# Libraries and Linker flags for compiling the binary file
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_gfx
LDFLAGS += -ldl -lpthread ${LIBS}

SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin
OUT = build

run: build
	./$(BIN)/$(OUT)

build: $(OBJ)
	mkdir -p ./$(BIN)
	$(CC) -o $(BIN)/$(OUT) $^ $(LDFLAGS)
	mv $^ $(BIN)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN)/* $(OBJ)