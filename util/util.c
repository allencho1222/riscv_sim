#include "util.h"

void program_head(void) {
	printf("************************************************\n");
	printf("\t\t\tRV32I ISS Project\t\t\t\n");
	printf("************************************************\n");
}

void program_output(struct display_data data) {
	int i = 0;
	FILE* mem_dump = fopen("mem_dump", "ab");
	printf("PC : 0x%08x\n", *data.pc);
	printf("IR : 0x%08x %s\n", *data.binary_inst, data.inst);

        if ((data.ctrl_sig)->mem_write) {
          printf("written data: %08x\n", *data.wr_data);
          printf("memory access: %08x\n", *data.addr);
        }
        if ((data.ctrl_sig)->mem_read) {
          printf("loaded data: %08x\n", *data.loaded_data);
          printf("memory access: %08x\n", *data.addr);
        }


	printf("GPR :");
	for (i = 0; i < 32; i++) {
		if (i % 4 == 0)
			printf("\n");
		
		printf("[%02d] : 0x%08x\t", i, data.reg_file[i]);
	}
	printf("\n---------------------------------------------------------\n");

	
	printf("memory image start\n");
}
