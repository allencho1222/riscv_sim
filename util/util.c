void program_head(void) {
	printf("************************************************\n");
	printf("\t\t\tRV32I ISS Project\t\t\t\n");
	printf("************************************************\n");
}

void program_output(struct display_data data) {
	int i = 0;
	printf("PC : %08x\n", data.pc);
	printf("IR : %08x (Instruction : %d)\n", data.ir, data.inst);

	printf("GPR :\n");
	for (i = 0; i < 32; i++) {
		if (i % 4 == 0)
			printf("\n");
		
		printf("[%02d] : %08x\t\n", i, data.reg_file[i]);
	}

	// TODO : memory write to binary file
}
