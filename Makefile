CC = gcc
CFLAGS = -Wall -O0

BIN_NAME = gameoflife

SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
INCLUDE_DIR = $(SRC_DIR)/include
OBJ_DIR = obj
BIN_DIR = bin

SRC_SOURCES = $(wildcard $(SRC_DIR)/*.c) 
LIB_SOURCES = $(wildcard $(LIB_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_SOURCES)) $(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIB_SOURCES))

TARGET = $(BIN_DIR)/$(BIN_NAME)

CFLAGS += -I$(INCLUDE_DIR)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CC) -g $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(notdir $@)

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJ_DIR)/$(notdir $@)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)