#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "5_stage/fetch.h"
#include "5_stage/decode.h"
#include "5_stage/alu.h"
#include "5_stage/memory.h"
#include "5_stage/registerfile.h"
#include "util/util.h"

#define PC_START 0x0

unsigned int register_file[32];
unsigned char memory[4096];

void execute(char* file_name, unsigned char cmd);
unsigned int get_alu_input1(struct ctrl_signal ctrl_sig, unsigned int rs1_data, unsigned int pc);
unsigned int get_alu_input2(struct ctrl_signal ctrl_sig, unsigned int rs2_data, unsigned int shm, unsigned int inst);
signed int get_imm_operand(unsigned int imm_type, unsigned int inst);

int main(int argc, char **argv) {
	//int opt;
	int break_point[10];
	int break_idx = 0;	// 0 : there was no break point
	char file_name[20];
	int i = 0;
	unsigned char command;

	strcpy(file_name, argv[1]);

	program_head();
	printf("Command : ");
	scanf("%c", &command); 

	execute(file_name, command);
	printf("------------------------------------------\n");

	return 0;
}

void execute(char* file_name, unsigned char cmd) {
	FILE* program = fopen(file_name, "rb");
	unsigned int pc = PC_START;
	unsigned int pc_copied = 0;	// for jal instruction
	unsigned int output_pc = 0;
	unsigned int fetched_inst;
	unsigned char command = cmd;
	struct display_data output;
	char *inst_str = (char *)malloc(10);

	while ((fetched_inst = fetch(program, &pc)) != (unsigned int) 0) {
		struct ctrl_signal ctrl_sig;
		struct two_reg_data reg_read_data;
		unsigned int rs1, rs2, rd;
		unsigned int alu_in1, alu_in2, alu_out;
		unsigned int memory_loaded_data;
		unsigned int reg_write_data;

		output_pc = pc - 0x4;
		// RISC-V architecture can extract rs1, rs2, rd before decoding
		// register file array starts at zero index, so we substract 1 from register
		rs1 = GET_RS1(fetched_inst);
		rs2 = GET_RS2(fetched_inst);
		rd = GET_RD(fetched_inst);

		ctrl_sig = decode(fetched_inst, inst_str);
		reg_read_data = register_read(register_file, rs1, rs2);


		// RS1 always goes into ALU, thus, we only consider RS2 type
		// RS1 can be zero or PC or RS1
		alu_in1 = get_alu_input1(ctrl_sig, reg_read_data.rs1_data, pc);
		alu_in2 = get_alu_input2(ctrl_sig, reg_read_data.rs2_data, GET_SHM(fetched_inst), fetched_inst);
		alu_out = alu(alu_in1, alu_in2, ctrl_sig.alu_fn);

		// if instruction is branch instruction and alu_out is 1
		if (ctrl_sig.is_branch && alu_out) {
			printf("branch occur \n");
			output_pc = pc - 0x4;
			pc += ((unsigned int)pc + ((unsigned int)SIGN_EXT_SB(GET_SB_IMM(fetched_inst)) * (unsigned int)2) - 0x4);
			// SEEK_CUR indicates next pc
			fseek(program, pc, SEEK_SET);
			goto OUTPUT;
			//continue;
		}
		if (ctrl_sig.is_jal || ctrl_sig.is_jalr) {
			printf("JAL or JALR occur\n");
			output_pc = pc - 0x4;
			pc_copied = pc;
			pc = alu_out;
			fseek(program, pc, SEEK_SET);
		}
		if (ctrl_sig.is_aui) {
			printf("AUIPC occur\n");
			output_pc = pc- 0x4;
			pc = alu_out;
			fseek(program, pc, SEEK_SET);
		}

		memory_loaded_data = memory_rw(memory, ctrl_sig.mem_write, ctrl_sig.mem_read, 
					ctrl_sig.mem_type, alu_out, reg_read_data.rs2_data);
		
		// data to register write : from memory or alu or pc
		reg_write_data = (ctrl_sig.mem_read) ? memory_loaded_data : 
				 (ctrl_sig.is_jalr || ctrl_sig.is_jal) ? pc_copied : alu_out;
		if (rd != 0) {
			register_write(register_file, rd, reg_write_data, ctrl_sig.reg_write);
		}

		OUTPUT:
		output.memory = memory;
		output.reg_file = register_file;
		output.pc = output_pc;
		output.binary_inst = fetched_inst;
		memcpy(output.inst, inst_str, 10);

		if (command == 'r')
			continue;

		program_output(output);
		printf("---------------------------------------------\n\n");

		printf("Command: ");
		scanf(" %c", &command);

		if (command == 's') {
			continue;
		} else if (command == 'r') {
			continue;
		} else {}
	}
}


unsigned int get_alu_input1(struct ctrl_signal ctrl_sig, unsigned int rs1_data, unsigned int pc) {
	if(ctrl_sig.rs1_type == RS1) {
		return rs1_data;
	} else if (ctrl_sig.rs1_type == PC) {
		return pc;
	} else if (ctrl_sig.rs1_type == ZERO) {
		return 0;
	} else {
		printf("wrong instruction came to alu input\n");
		return 0;
	}
}


unsigned int get_alu_input2(struct ctrl_signal ctrl_sig, unsigned int rs2_data, unsigned int shm, unsigned int inst) {
	if(ctrl_sig.rs2_type == RS2) {
		return rs2_data;
	} else if (ctrl_sig.rs2_type == SHM) {
		return shm;
	} else if (ctrl_sig.rs2_type == IMM) {
		return get_imm_operand(ctrl_sig.imm_type, inst);
	} else {
		printf("wrong instruction came to alu input\n");
		return 0;
	}
}

signed int get_imm_operand(unsigned int imm_type, unsigned int inst) {
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
