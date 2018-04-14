#include "decode.h"

void set_ctrl_sig(struct ctrl_signal *ctrl_sig,
		  int alu_fn,
		  int imm_type,
		  int rs1_type,
		  int rs2_type,
		  int mem_type,
		  int reg_write,
		  int mem_write,
		  int mem_read,
		  int is_branch,
		  int is_jalr,
		  int is_jal,
		  int is_aui) {
	ctrl_sig->alu_fn = alu_fn;
	ctrl_sig->imm_type = imm_type;
	ctrl_sig->rs1_type = rs1_type;
	ctrl_sig->rs2_type = rs2_type;
	ctrl_sig->mem_type = mem_type;
	ctrl_sig->reg_write = reg_write;
	ctrl_sig->mem_write = mem_write;
	ctrl_sig->mem_read = mem_read;
	ctrl_sig->is_branch = is_branch;
	ctrl_sig->is_jalr = is_jalr;
	ctrl_sig->is_jal = is_jal;
	ctrl_sig->is_aui = is_aui;
}


struct ctrl_signal decode(unsigned int inst, char* inst_str) {
	struct ctrl_signal ctrl_sig;
	switch (GET_OP(inst)) {
		case LUI:
			set_ctrl_sig(&ctrl_sig, ALU_LUI, IMM_U, ZERO, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
			strcpy(inst_str, "LUI");
			break;
		case AUIPC:
			set_ctrl_sig(&ctrl_sig, ALU_AUIPC, IMM_U, PC, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 1);
			strcpy(inst_str, "AUIPC");
			break;
		case JAL:
			set_ctrl_sig(&ctrl_sig, ALU_JAL, IMM_UJ, PC, IMM, FN3_NONE, 1, 0, 0, 0, 0, 1, 0);
			strcpy(inst_str, "JAL");
			break;
		default:
			switch(GET_OP(inst) | GET_FN3(inst)) {
				case JALR:
					set_ctrl_sig(&ctrl_sig, ALU_JALR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 1, 0, 0);
					strcpy(inst_str, "JALR");
					break;
				case LB:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, BYTE, 1, 0, 1, 0, 0, 0, 0);
					strcpy(inst_str, "LB");
					break;
				case LH:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, HALF, 1, 0, 1, 0, 0, 0, 0);
					strcpy(inst_str, "LH");
					break;
				case LW:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, WORD, 1, 0, 1, 0, 0, 0, 0);
					strcpy(inst_str, "LW");
					break;
				case LBU:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, BYTEU, 1, 0, 1, 0, 0, 0, 0);
					strcpy(inst_str, "LBU");
					break;
				case LHU:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, HALFU, 1, 0, 1, 0, 0, 0, 0);
					strcpy(inst_str, "LHU");
					break;
				case SB:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, BYTE, 0, 1, 0, 0, 0, 0, 0);
					strcpy(inst_str, "SB");
					break;
				case SH:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, HALF, 0, 1, 0, 0, 0, 0, 0);
					strcpy(inst_str, "SH");
					break;
				case SW:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, WORD, 0, 1, 0, 0, 0, 0, 0);
					strcpy(inst_str, "SW");
					break;
				case ADDI:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "ADDI");
					break;
				case SLTI:
					set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "SLTI");
					break;
				case SLTIU:
					set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "SLTIU");
					break;
				case XORI:
					set_ctrl_sig(&ctrl_sig, ALU_XOR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "XORI");
					break;
				case ORI:
					set_ctrl_sig(&ctrl_sig, ALU_OR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "ORI");
					break;
				case ANDI:
					set_ctrl_sig(&ctrl_sig, ALU_AND, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
					strcpy(inst_str, "ANDI");
					break;
				case BEQ:
					set_ctrl_sig(&ctrl_sig, ALU_SEQ, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BEQ");
					break;
				case BNE:
					set_ctrl_sig(&ctrl_sig, ALU_SNE, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BNE");
					break;
				case BLT:
					set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BLT");
					break;
				case BGE:
					set_ctrl_sig(&ctrl_sig, ALU_SGE, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BGE");
					break;
				case BLTU:
					set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BLTU");
					break;
				case BGEU:
					set_ctrl_sig(&ctrl_sig, ALU_SGEU, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
					strcpy(inst_str, "BGEU");
					break;
				default:
					switch(GET_OP(inst) | GET_FN3(inst) | GET_FN7(inst)) {
						case SLLI:
							set_ctrl_sig(&ctrl_sig, ALU_SLL, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SLLI");
							break;
						case SRLI:
							set_ctrl_sig(&ctrl_sig, ALU_SRL, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SRLI");
							break;
						case SRAI:
							set_ctrl_sig(&ctrl_sig, ALU_SRA, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SRAI");
							break;
						case ADD:
							set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "ADD");
							break;
						case SUB:
							set_ctrl_sig(&ctrl_sig, ALU_SUB, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SUB");
							break;
						case SLL:
							set_ctrl_sig(&ctrl_sig, ALU_SLL, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SLL");
							break;
						case SLT:
							set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SLT");
							break;
						case SLTU:
							set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SLTU");
							break;
						case XOR:
							set_ctrl_sig(&ctrl_sig, ALU_XOR, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "XOR");
							break;
						case SRL:
							set_ctrl_sig(&ctrl_sig, ALU_SRL, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SRL");
							break;
						case SRA:
							set_ctrl_sig(&ctrl_sig, ALU_SRA, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "SRA");
							break;
						case OR:
							set_ctrl_sig(&ctrl_sig, ALU_OR, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "OR");
							break;
						case AND:
							set_ctrl_sig(&ctrl_sig, ALU_AND, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
							strcpy(inst_str, "AND");
							break;
						default:
							printf("instruction type is error\n");
					}
			}
	}
	return ctrl_sig;
}
