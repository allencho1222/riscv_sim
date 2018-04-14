unsigned int fetch(FILE* program, unsigned int* pc) {
	unsigned char inst[4];
	unsigned int binary_inst = 0b0;

	fread(inst, sizeof(inst), 1, program);
	
	for (i = sizeof(inst) - 1; i >= 0; i--) {
		binary_inst |= ((unsigned int) inst[i] << (i * 8));
	}
	(*pc) += ftell(program);

	return binary_inst;
}
