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
                        sprintf(inst_str, "(Instruction : LUI x%d, 0x%x)", GET_RD(inst), GET_U_IMM(inst) >> 12);
			break;
		case AUIPC:
			set_ctrl_sig(&ctrl_sig, ALU_AUIPC, IMM_U, PC, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 1);
                        sprintf(inst_str, "(Instruction : AUIPC x%d, 0x%x)", GET_RD(inst), GET_U_IMM(inst) >> 12);
			break;
		case JAL:
			set_ctrl_sig(&ctrl_sig, ALU_JAL, IMM_UJ, PC, IMM, FN3_NONE, 1, 0, 0, 0, 0, 1, 0);
                        sprintf(inst_str, "(Instruction : JAL x%d, 0x%x)", GET_RD(inst), GET_UJ_IMM(inst));
			break;
		default:
			switch(GET_OP(inst) | GET_FN3(inst)) {
				case JALR:
					set_ctrl_sig(&ctrl_sig, ALU_JALR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 1, 0, 0);
                                        sprintf(inst_str, "(Instruction : JALR x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case LB:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, BYTE, 1, 0, 1, 0, 0, 0, 0);
                                        //sprintf(inst_str, "(Instruction : LB x%d, %d(x%d))", GET_RD(inst), SIGN_EXT_I(GET_I_IMM(inst)), RS1(inst));
                                        sprintf(inst_str, "(Instruction : LB x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case LH:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, HALF, 1, 0, 1, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : LH x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case LW:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, WORD, 1, 0, 1, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : LW x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case LBU:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, BYTEU, 1, 0, 1, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : LBU x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case LHU:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, HALFU, 1, 0, 1, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : LHU x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case SB:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, BYTE, 0, 1, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : SB x%d, x%d, %d)", GET_RS1(inst), GET_RS2(inst), GET_S_IMM(inst));
					break;
				case SH:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, HALF, 0, 1, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : SH x%d, x%d, %d)", GET_RS1(inst), GET_RS2(inst), GET_S_IMM(inst));
					break;
				case SW:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_S, RS1, IMM, WORD, 0, 1, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : SW x%d, x%d, %d)", GET_RS1(inst), GET_RS2(inst), GET_S_IMM(inst));
					break;
				case ADDI:
					set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : ADDI x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case SLTI:
					set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : SLTI x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case SLTIU:
					set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : SLTIU x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case XORI:
					set_ctrl_sig(&ctrl_sig, ALU_XOR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : XORI x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case ORI:
					set_ctrl_sig(&ctrl_sig, ALU_OR, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : ORI x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case ANDI:
					set_ctrl_sig(&ctrl_sig, ALU_AND, IMM_I, RS1, IMM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : ANDI x%d, x%d, 0x%x)", GET_RD(inst), GET_RS1(inst), GET_I_IMM(inst));
					break;
				case BEQ:
					set_ctrl_sig(&ctrl_sig, ALU_SEQ, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BEQ x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				case BNE:
					set_ctrl_sig(&ctrl_sig, ALU_SNE, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BNE x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				case BLT:
					set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BLT x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				case BGE:
					set_ctrl_sig(&ctrl_sig, ALU_SGE, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BGE x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				case BLTU:
					set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BLTU x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				case BGEU:
					set_ctrl_sig(&ctrl_sig, ALU_SGEU, IMM_SB, RS1, RS2, FN3_NONE, 0, 0, 0, 1, 0, 0, 0);
                                        sprintf(inst_str, "(Instruction : BGEU x%d, x%d, 0x%x)", GET_RS1(inst), GET_RS2(inst), GET_SB_IMM(inst));
					break;
				default:
					switch(GET_OP(inst) | GET_FN3(inst) | GET_FN7(inst)) {
						case SLLI:
							set_ctrl_sig(&ctrl_sig, ALU_SLL, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SLLI x%d, x%d, %d)", GET_RD(inst), GET_RS1(inst), GET_SHM(inst));
							break;
						case SRLI:
							set_ctrl_sig(&ctrl_sig, ALU_SRL, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SRLI x%d, x%d, %d)", GET_RD(inst), GET_RS1(inst), GET_SHM(inst));
							break;
						case SRAI:
							set_ctrl_sig(&ctrl_sig, ALU_SRA, IMM_NONE, RS1, SHM, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SRAI x%d, x%d, %d)", GET_RD(inst), GET_RS1(inst), GET_SHM(inst));
							break;
						case ADD:
							set_ctrl_sig(&ctrl_sig, ALU_ADD, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : ADD x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SUB:
							set_ctrl_sig(&ctrl_sig, ALU_SUB, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SUB x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SLL:
							set_ctrl_sig(&ctrl_sig, ALU_SLL, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SLL x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SLT:
							set_ctrl_sig(&ctrl_sig, ALU_SLT, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SLT x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SLTU:
							set_ctrl_sig(&ctrl_sig, ALU_SLTU, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SLTU x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case XOR:
							set_ctrl_sig(&ctrl_sig, ALU_XOR, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : XOR x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SRL:
							set_ctrl_sig(&ctrl_sig, ALU_SRL, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SRL x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case SRA:
							set_ctrl_sig(&ctrl_sig, ALU_SRA, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : SRA x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case OR:
							set_ctrl_sig(&ctrl_sig, ALU_OR, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : OR x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						case AND:
							set_ctrl_sig(&ctrl_sig, ALU_AND, IMM_NONE, RS1, RS2, FN3_NONE, 1, 0, 0, 0, 0, 0, 0);
                                                        sprintf(inst_str, "(Instruction : AND x%d, x%d, x%d)", GET_RD(inst), GET_RS1(inst), GET_RS2(inst));
							break;
						default:
							printf("instruction type is error\n");
					}
			}
	}
	return ctrl_sig;
}
