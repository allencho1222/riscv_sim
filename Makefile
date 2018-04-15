CC = gcc
SUB_DIR = 5_stage
OBJS = $(SUB_DIR)/fetch.o $(SUB_DIR)/decode.o $(SUB_DIR)/alu.o $(SUB_DIR)/memory.o $(SUB_DIR)/registerfile.o
TARGET = rv32i_iss

$(TARGET) : main.o $(OBJS) util/util.o
	$(CC) -o $(TARGET) $(OBJS)

$(SUB_DIR)/%.o: $(SUB_DIR)/%.c
	$(CC) -c $< -o $@

util/util.o: util/util.c
	$(CC) -c util/util.c -o util/util.o

main.o: main.c
	$(CC) -c main.c
