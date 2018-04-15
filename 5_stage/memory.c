#include "memory.h"

#define BYTE_SIGN_EXT(X)	((((X) >> (7)) == 0) ? (X) : ((-1) ^ (0xFF) | (X)))
#define HALF_SIGN_EXT(X)	((((X) >> (15)) == 0) ? (X) : ((-1) ^ (0xFFFF) | (X)))

unsigned int memory_rw(unsigned char* memory, 
		       unsigned int mem_write, 
		       unsigned int mem_read,
		       unsigned int mem_type, 
		       unsigned int addr, 
		       unsigned int data) {

	unsigned int loaded_data = 0;

	if (!mem_read && !mem_write)
		return 0;

	//printf("memory access address : %08x(%d)\n", addr, addr);
	// load
	if (mem_read) {
		switch (mem_type) {
			case BYTE:
				memcpy(&loaded_data, memory + addr, 1);
				loaded_data = BYTE_SIGN_EXT(loaded_data);
				break;
			case HALF:
				memcpy(&loaded_data, memory + addr, 2);
				loaded_data = HALF_SIGN_EXT(loaded_data);
				break;
			case WORD:
				memcpy(&loaded_data, memory + addr, 4);
				break;
			case BYTEU:
				memcpy(&loaded_data, memory + addr, 1);
				//loaded_data = loaded_data & 0b00000000000000000000000011111111;
				break;
			case HALFU:
				memcpy(&loaded_data, memory + addr, 2);
				//loaded_data = loaded_data & 0b00000000000000001111111111111111;
				break;
			default:
				printf("memory type is error\n");
		}
                //printf("loaded data: %08x\n", loaded_data);
	}

	// store
	if (mem_write) {
			//printf("memory write data : %08x\n", data);
		switch (mem_type) {
			case BYTE:
				memcpy(memory + addr, &data, 1);
				break;
			case HALF:
				memcpy(memory + addr, &data, 2);
				break;
			case WORD:
				memcpy(memory + addr, &data, 4);
				break;
			default:
				printf("memory type is error\n");
		}
	}
	return loaded_data;
}
