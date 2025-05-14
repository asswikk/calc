CC = gcc

CFLAGS = -Wall -Wextra -g -std=c11 -DDEBUG -I$(SRC_DIR) -I$(INPUT_DIR) -I$(LIST_DIR) -I$(SERVER_DIR) -I$(MONGOOSE_DIR) -fsanitize=address

SRC_DIR = src
INPUT_DIR = $(SRC_DIR)/input
LIST_DIR = $(SRC_DIR)/list
SERVER_DIR = $(SRC_DIR)/server
MONGOOSE_DIR = mongoose

OBJ = $(SRC_DIR)/main.o $(INPUT_DIR)/input.o $(LIST_DIR)/list.o $(SERVER_DIR)/server.o $(MONGOOSE_DIR)/mongoose.o

TARGET = server_main

SRCS = $(SRC_DIR)/main.c $(INPUT_DIR)/input.c $(LIST_DIR)/list.c $(SERVER_DIR)/server.c $(MONGOOSE_DIR)/mongoose.c

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

rebuild: clean $(TARGET)

cppcheck: 
	cppcheck --enable=all --suppress=missingInclude --suppress=missingIncludeSystem --platform=unix64 $(SRCS)

