CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = vm
DIST_DIR = dist

SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/fs/fs.c \
      $(SRC_DIR)/interpreter/interpreter.c \
      $(SRC_DIR)/repl/repl.c \
      $(SRC_DIR)/alu/alu.c

OBJ = $(DIST_DIR)/main.o \
      $(DIST_DIR)/fs.o \
      $(DIST_DIR)/interpreter.o \
      $(DIST_DIR)/repl.o \
      $(DIST_DIR)/alu.o

TARGET = $(DIST_DIR)/vm

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(DIST_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIST_DIR)/fs.o: $(SRC_DIR)/fs/fs.c
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIST_DIR)/interpreter.o: $(SRC_DIR)/interpreter/interpreter.c
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIST_DIR)/repl.o: $(SRC_DIR)/repl/repl.c
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIST_DIR)/alu.o: $(SRC_DIR)/alu/alu.c
	@mkdir -p $(DIST_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
