unsigned int fetch(FILE* program, unsigned int* pc) {
	unsigned char inst[4];
	unsigned int binary_inst = 0b0;

	fread(inst, sizeof(inst), 1, program);
	printf("PC: %u\t", *pc);
	
	for (i = sizeof(inst) - 1; i >= 0; i--) {
		binary_inst |= ((unsigned int) inst[i] << (i * 8));
	}
	(*pc) += 0x4;

	prtinf("%x\n", binary_inst);

	return binary_inst;
}
