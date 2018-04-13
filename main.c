#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PC_START 0x0

unsigned int register_file[32];
unsigned char memory[4096];

void execute_one(char* file_name);

int main(int argc, char **argv) {
	int opt;
	int break_point[10];
	int break_idx = 0;	// 0 : there was no break point
	char file_name[20];
	int i = 0;

	while((opt = getopt(argc, argv, "srjb:f:")) != -1) {
		switch(opt) {
			case 'f':
				strcpy(file_name, optarg);
				break;
			case 's':
				printf("Command : %c\n", opt);
				execute_one(file_name);
				break;
			case 'r':
				printf("Command : %c\n", opt);
				//execute_entire();
				break;
			case 'j':
				printf("until next break point\n");
				break;
			case 'b':
				// up to 10 break point
				break_point[break_idx++] = atoi(optarg);
				break;
			default:
				printf("option end\n");
		}
	}
	return 0;
}

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

unsign

void execute_one(char* file_name) {
	FILE* program = fopen(file_name, "rb");
	unsigned int pc = PC_START;
	unsigned int fetched_inst;

	//fetch(program, &pc);
	// TODO : if the instruction is branch, then instruction fetch starts at brancehd location
	while ((fetched_inst = fetch(program, &pc)) != (unsigned int) 0) {
		struct ctrl_signal ctrl_sig;
		struct two_reg_data reg_read_data;
		unsigned int reg_write_data;
		unsigned int rs1, rs2, rd;
		unsigned int alu_in1, alu_in2, alu_out;

		// RISC-V architecture can extract rs1, rs2, rd before decoding
		rs1 = GET_RS1(fetched_inst);
		rs2 = GET_RS2(fetched_inst);
		rs3 = GET_RS3(fetched_inst);

		ctrl_sig = decode(fetched_inst);
		reg_read_data = register_read(register_file, rs1, rs2);

		// TODO : special case -> LUI, AUIPC, JAL
		// RS1 always goes into ALU, thus, we only consider RS2 type
		// TODO : consider store instruction
		alu_in1 = reg_data.rs1_data;
		if(ctrl_sig.rs2_type == RS2) {
			alu_in2 = reg_data.rs2_data;
		} else if (ctrl_sig.rs2_type == SHM) {
			alu_in2 = GET_SHM(inst);
		} else if (ctrl_sig.rs2_type == IMM) {
			// TODO : maybe need more classification
			if (ctrl_sig.imm_type == IMM_I) {
				alu_in2 = GET_I_IMM(inst);
			} else if (ctrl_sig.imm_type == IMM_S) {
				alu_in2 = GET_S_IMM(inst);
			}
		} else {
			printf("wrong instruction came to alu input\n")
		}
		alu_out = alu(alu_in1, alu_in2, ctrl_sig.alu_fn);

		// FN3_NONE should not generate output_value from memory
		memory_rw(memory, ctrl_sig.mem_write, ctrl_sig.ctrl_sig.mem_type, alu_out, reg_read_data.rs2_data);
		
		// data to register write : from memory or alu

		register_write(register_file, rd, ctrl_sig.reg_write);
	}
}
