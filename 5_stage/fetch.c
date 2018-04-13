#include "fetch.h"

unsigned int fetch(FILE* program, unsigned int* pc) {
	int i = 0;
	unsigned char inst[4];
	unsigned int binary_inst = 0b0;

	if (fread(inst, sizeof(inst), 1, program) == 0) {
		return 0;
	}
	printf("PC: %08x\t", *pc);
	
	// convert binary data into unsigned integer
	// has to consider little-endian form
	for (i = sizeof(inst) - 1; i >= 0; i--)
		binary_inst |= ((unsigned int) inst[i] << (i * 8));

	(*pc) += 0x4;

	printf("%08x\n", binary_inst);

	return binary_inst;
}
