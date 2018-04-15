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
#define SP_START 0xF00
#define GP_START 0x100

#define BP_LIMIT 10

unsigned int register_file[32];
unsigned char memory[4096];

unsigned char bp[11];
int bp_front = 0;
int bp_rear = 0;

char command[50];

unsigned int jump_point = -1;

void enqueue_bp (unsigned int break_point) {
  if ((bp_rear + 1) % 11 == bp_front) {
    printf("no more break point\n");
    return;
  }

  bp[bp_rear++] = break_point;
}

unsigned int dequeue_bp () {
  return bp[bp_front++];
}

int is_bp_empty() {
  return (bp_front == bp_rear) ? 1 : 0;
}

  
void execute(char* file_name);
unsigned int get_alu_input1(struct ctrl_signal ctrl_sig, unsigned int rs1_data, unsigned int pc);
unsigned int get_alu_input2(struct ctrl_signal ctrl_sig, unsigned int rs2_data, unsigned int shm, unsigned int inst);
signed int get_imm_operand(unsigned int imm_type, unsigned int inst);

int main(int argc, char **argv) {
	//int opt;
	int break_point[10];
	int break_idx = 0;	// 0 : there was no break point
	char file_name[100];
	int i = 0;
	FILE* memory_dump = fopen("mem_dump", "wb");

	strcpy(file_name, argv[1]);

	register_file[2] = SP_START;	// init sp
	register_file[3] = GP_START;	// init gp

	program_head();

        // command processing logic
        while (1) {
          printf("Command: ");
          fgets(command, 50, stdin);
          if (command[0] == 's') {
            break;
          } else if (command[0] == 'b') {
            enqueue_bp (atoi(command + 2));
          } else if (command[0] == 'j') {
            if (is_bp_empty()) {
              printf("no break point exists\n");
            } else {
              jump_point = dequeue_bp();
              break;
            }
          } else if (command[0] == 'r'){  // r
            break;
          } else {
            printf("wrong command\n");
          }
        }
        
        // run simulator
	execute(file_name);
	

	for (i = 0; i < 4096; i++) {
		fwrite(memory + i, 1, 1, memory_dump);
	}

	return 0;
}

void execute(char* file_name) {
	FILE* program = fopen(file_name, "rb");
	unsigned int pc = PC_START;
	unsigned int pc_copied = 0;	// for jal instruction
	unsigned int output_pc = 0;
	unsigned int fetched_inst;
	struct display_data output;
	char *inst_str = (char *)malloc(100);
	int i = 0;

	output.memory = memory;
	output.reg_file = register_file;
	output.pc = &output_pc;
	output.binary_inst = &fetched_inst;
	output.inst = inst_str;

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

		alu_in1 = get_alu_input1(ctrl_sig, reg_read_data.rs1_data, pc - 0x4);
		alu_in2 = get_alu_input2(ctrl_sig, reg_read_data.rs2_data, GET_SHM(fetched_inst), fetched_inst);
		alu_out = alu(alu_in1, alu_in2, ctrl_sig.alu_fn);
                //
		// if instruction is branch instruction and alu_out is 1
		if (ctrl_sig.is_branch && alu_out) {
			signed int offset = SIGN_EXT_SB(GET_SB_IMM(fetched_inst)) * 2;
			pc = pc - 0x4 + offset;
			fseek(program, pc, SEEK_SET);
		}
		if (ctrl_sig.is_jal) {
			pc_copied = pc;
			pc = alu_out;
			fseek(program, pc, SEEK_SET);
		}
		if (ctrl_sig.is_jalr) {
			pc_copied = pc;
			pc = alu_out;
			fseek(program, pc, SEEK_SET);
			if (register_file[1] == 0xc) {
				program_output(output);	// 'r' command stops here
				break;
			}
		}

		memory_loaded_data = memory_rw(memory, ctrl_sig.mem_write, ctrl_sig.mem_read, 
					ctrl_sig.mem_type, alu_out, reg_read_data.rs2_data);
		
		reg_write_data = (ctrl_sig.mem_read) ? memory_loaded_data : 
				 (ctrl_sig.is_jalr || ctrl_sig.is_jal) ? pc_copied : alu_out;
		if (rd != 0) {
			register_write(register_file, rd, reg_write_data, ctrl_sig.reg_write);
		}

                // command processing logic
		if (command[0] == 'r')
			continue;

                if (command[0] != 'j') {               // only s and j can be here;
                  program_output(output);
                } else if (command[0] == 'j' && jump_point != -1) {
                  if (jump_point == output_pc) {
                    jump_point = -1;
                    program_output(output);
                  } else {
                    continue;
                  }
                } else {}

                while (1) {
                  printf("Command: ");
                  fgets(command, 50, stdin);
                  if (command[0] == 's') {
                    break;
                  } else if (command[0] == 'b') {
                    enqueue_bp (atoi(command + 2));
                  } else if (command[0] == 'j') {
                    if (is_bp_empty()) {
                      printf("no break point exists\n");
                    } else {
                      jump_point = dequeue_bp();
                      printf("jump_point : %d \n", jump_point);
                      break;
                    }
                  } else if (command[0] == 'r'){  // r
                    break;
                  } else {
                    printf("wrong command\n");
                  }
                }
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
		//return SIGN_EXT_U(GET_U_IMM(inst));
		return GET_U_IMM(inst);
	} else if (imm_type == IMM_UJ) {
		return SIGN_EXT_UJ(GET_UJ_IMM(inst));
	} else {	// IMM_NONE
		printf("current instruction does not have immediate field\n");
		return 0;
	}
}
