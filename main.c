#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "5_stage/fetch.h"
#include "5_stage/decode.h"
#include "5_stage/alu.h"
#include "5_stage/memory.h"
#include "5_stage/registerfile.h"

#define PC_START 0x0

unsigned int register_file[32];
unsigned char memory[4096];

void execute_one(char* file_name);

int main(int argc, char **argv) {
	//int opt;
	int break_point[10];
	int break_idx = 0;	// 0 : there was no break point
	char file_name[20];
	int i = 0;
	char command;

	strcpy(file_name, argv[1]);

	program_head();
	printf("Command : ");
	scanf("%c", &command);

	// TODO : program launch;
	execute(file_name, command);
	printf("------------------------------------------\n");
	program_output();

	/*
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
	*/
	return 0;
}

void execute(char* file_name, char command) {
	FILE* program = fopen(file_name, "rb");
	unsigned int pc = PC_START;
	unsigned int fetched_inst;

	//fetch(program, &pc);
	// TODO : if the instruction is branch, then instruction fetch starts at brancehd location
	while ((fetched_inst = fetch(program, &pc)) != (unsigned int) 0) {
		struct ctrl_signal ctrl_sig;
		struct two_reg_data reg_read_data;
		unsigned int rs1, rs2, rd;
		unsigned int alu_in1, alu_in2, alu_out;
		unsigned int memory_loaded_data;
		unsigned int reg_write_data;

		// RISC-V architecture can extract rs1, rs2, rd before decoding
		rs1 = GET_RS1(fetched_inst);
		rs2 = GET_RS2(fetched_inst);
		rd = GET_RD(fetched_inst);

		ctrl_sig = decode(fetched_inst);
		reg_read_data = register_read(register_file, rs1, rs2);

		// TODO : special case -> LUI, AUIPC, JAL
		// RS1 always goes into ALU, thus, we only consider RS2 type
		alu_in1 = reg_data.rs1_data;
		alu_in2 = get_alu_input2(ctrl_sig.rs2_type, reg_data.rs2_data);
		alu_out = alu(alu_in1, alu_in2, ctrl_sig.alu_fn);

		memory_loaded_data = memory_rw(memory, ctrl_sig.mem_write, ctrl_sig.mem_read, 
					ctrl_sig.ctrl_sig.mem_type, alu_out, reg_read_data.rs2_data);
		
		// data to register write : from memory or alu
		reg_write_data = (ctrl_sig.mem_read) ? memory_loaded_data : alu_out;
		register_write(register_file, rd, reg_write_data, ctrl_sig.reg_write);
		if (command == 's')
			break;
	}
}

unsigned int get_alu_input2(struct ctrl_signal ctrl_sig, unsigned int rs2_data) {
	if(ctrl_sig.rs2_type == RS2) {
		return rs2_data;
	} else if (ctrl_sig.rs2_type == SHM) {
		return GET_SHM(inst);
	} else if (ctrl_sig.rs2_type == IMM) {
		return get_imm_operand(ctrl_sig.imm_type);
	} else {
		printf("wrong instruction came to alu input\n")
	}
}

unsigned int get_imm_operand(unsigned int imm_type) {
	if (imm_type == IMM_I) {
		return SIGN_EXT_I(GET_I_IMM(inst));
	} else if (imm_type == IMM_S) {
		return SIGN_EXT_S(GET_S_IMM(inst));
	} else if (imm_type == IMM_SB) {
		return SIGN_EXT_SB(GET_SB_IMM(inst));
	} else if (imm_type == IMM_U) {
		return SIGN_EXT_U(GET_U_IMM(inst));
	} else if (imm_type == IMM_UJ) {
		return SIGN_EXT_UJ(GET_UJ_IMM(inst));
	} else {	// IMM_NONE
		printf("current instruction does not have immediate field\n");
		return 0;
	}
}
