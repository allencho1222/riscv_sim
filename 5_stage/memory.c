#include "memory.h"

unsigned int memory_rw(unsigned char* memory, unsigned int mem_write, unsigned int mem_read, unsigned int mem_type, unsigned int addr, unsigned int data) {
	// BYTE : 0, HALF : 2, WORD : 4
	
	//int data_type = (int)pow((double) 2, (double) (mem_type >> 12));
	unsigned int data_loaded = 0;

	// for mempcy to copy at least 1 byte
	//if (data_type == 0) {
		//data_type += 1;
	//}
	// Store instruction
	// copy the rs2 data into the memory
	// data is arranged in little-endian order
	
	// no memory operation
	if (mem_write == 0 && mem_read == 0)
		return 0;

	// store operation : BYTE, HALF, WORD	
	// our 'data' is already arranged in little-endian order
	if (mem_write) {
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
				printf("memory data type error\n");
				break;
		}
	}
	if (mem_read) {
		switch (mem_type) {
			case BYTE:
				memcpy(&data_loaded, memory + addr, 1);
				data_loaded = (data_loaded >> 7 == 0) ? data_loaded : (-1 ^ 0xFF) | data_loaded;
				break;
			case HALF:
				memcpy(&data_loaded, memory + addr, 2);
				data_loaded = (data_loaded >> 15 == 0) ? data_loaded : (-1 ^ 0xFFFF) | data_loaded;
				break;
			case WORD:
				memcpy(&data_loaded, memory + addr, 4);
				break;
			case BYTEU:
				memcpy(&data_loaded, memory + addr, 1);
				break;
			case HALFU:
				memcpy(&data_loaded, memory + addr, 2);
				break;
			default:
				printf("memory data type error\n");
				break;
		}
	}
	return data_loaded;
}
