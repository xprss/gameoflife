CC = gcc
CFLAGS = -Wall -O2
SRC_DIR = .
LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin
SOURCES = $(wildcard $(SRC_DIR)/*.c $(LIB_DIR)/field/*.c $(LIB_DIR)/shlib/*.c $(LIB_DIR)/vec2/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = $(BIN_DIR)/gameoflife

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)