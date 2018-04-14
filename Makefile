CC = gcc
SUB_DIR = 5_stage
OBJS = $(SUB_DIR)/fetch.o $(SUB_DIR)/decode.o $(SUB_DIR)/alu.o $(SUB_DIR)/memory.o $(SUB_DIR)/registerfile.o

sim : main.o $(OBJS)
	$(CC) -o sim fetch.o decode.o alu.o memory.o registerfile.o

$(SUB_DIR)/fetch.o: $(SUB_DIR)/fetch.c
	$(CC) -c $< 

$(SUB_DIR)/decode.o: $(SUB_DIR)/decode.c
	$(CC) -c $<

$(SUB_DIR)/alu.o: $(SUB_DIR)/alu.c
	$(CC) -c $<

$(SUB_DIR)/memory.o: $(SUB_DIR)/memory.c
	$(CC) -c $<

$(SUB_DIR)/registerfile.o: $(SUB_DIR)/registerfile.c
	$(CC) -c $<

main.o: main.c
	$(CC) -c $<
