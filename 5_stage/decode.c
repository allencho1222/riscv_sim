#include "decode.h"

void set_load_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
  ctrl_sig->alu_fn = ALU_ADD;
  ctrl_sig->imm_type = IMM_I;
  ctrl_sig->rs1_type = RS1;
  ctrl_sig->rs2_type = IMM;
  ctrl_sig->mem_type = MEM_TYPE(inst);
  ctrl_sig->reg_write = 1;
  ctrl_sig->mem_write = 0;
  ctrl_sig->mem_read = 1;
} 

void set_store_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
  ctrl_sig->alu_fn = ALU_ADD;
  ctrl_sig->imm_type = IMM_S;
  ctrl_sig->rs1_type = RS1;
  ctrl_sig->rs2_type = IMM;
  ctrl_sig->mem_type = MEM_TYPE(inst);
  ctrl_sig->reg_write = 0;
  ctrl_sig->mem_write = 1;
  ctrl_sig->mem_read = 0;
}

void set_arith_imm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst);
	if (alu_type == 0b101) {
		if (GET_FN7(inst) >> 25 == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else if (alu_type == 0b000) {
		if (GET_FN7(inst) >> 25 == 0b0000000) {
			alu_type = ALU_SUB;
		} else {
			alu_type = ALU_ADD;
		}
	} else {}
	ctrl_sig->alu_fn = alu_type;
	ctrl_sig->imm_type = IMM_I;
	ctrl_sig->rs1_type = RS1;
	ctrl_sig->rs2_type = IMM;
	ctrl_sig->mem_type = FN3_NONE;
  	ctrl_sig->reg_write = 1;
	ctrl_sig->mem_write = 0;
}

void set_branch_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	// TODO : branch alu type
	ctrl_sig->alu_fn = ALU_TYPE(inst);
	ctrl_sig->imm_type = IMM_SB;
	ctrl_sig->rs1_type = RS1;
	ctrl_sig->rs2_type = RS2;
	ctrl_sig->mem_type = FN3_NONE;
  	ctrl_sig->reg_write = 0;
	ctrl_sig->mem_write = 0;
	ctrl_sig->mem_read = 0;
}

void set_arith_norm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst);
	if (alu_type == 0b101) {
		if (GET_FN7(inst) >> 25 == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else if (alu_type == 0b000) {
		if (GET_FN7(inst) >> 25 == 0b0000000) {
			alu_type = ALU_SUB;
		} else {
			alu_type = ALU_ADD;
		}
	} else {}
	ctrl_sig->alu_fn = alu_type;
	ctrl_sig->imm_type = IMM_NONE;
	ctrl_sig->rs1_type = RS1;
	ctrl_sig->rs2_type = RS2;
	ctrl_sig->mem_type = FN3_NONE;
  	ctrl_sig->reg_write = 1;
	ctrl_sig->mem_write = 0;
	ctrl_sig->mem_read = 0;
}

void set_arith_shift_shm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst);
	if (alu_type == 0b101) {
		if (GET_FN7(inst) >> 25 == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else {}
	ctrl_sig->alu_fn = alu_type;
	ctrl_sig->imm_type = IMM_NONE;
	ctrl_sig->rs1_type = RS1;
	ctrl_sig->rs2_type = SHM;
	ctrl_sig->mem_type = FN3_NONE;
  	ctrl_sig->reg_write = 1;
	ctrl_sig->mem_write = 0;
	ctrl_sig->mem_read = 0;
}

struct ctrl_signal decode(unsigned int inst) {
	struct ctrl_signal ctrl_sig;
	switch (GET_OP(inst) | GET_FN3(inst)) {
		case LB:
		case LH:
		case LW:
		case LBU:
		case LHU:
			set_load_sig(inst, &ctrl_sig);
			break;
		case SB:
		case SH:
		case SW:
			set_store_sig(inst, &ctrl_sig);
			break;
		case ADDI:
		case SLTI:
		case SLTIU:
		case XORI:
		case ORI:
		case ANDI:
			set_arith_imm_sig(inst, &ctrl_sig);
			break;
		case BEQ:
		case BNE:
		case BLT:
		case BGE:
		case BLTU:
		case BGEU:
			set_branch_sig(inst, &ctrl_sig);
			break;
		case LUI:
			// TODO
			break;
		case AUIPC:
			// TODO
			break;
		case JAL:
			// TODO
			break;
		case JALR:
			// TODO
			break;
		default:
			switch (GET_OP(inst) | GET_FN3(inst) | GET_FN7(inst)) {
				case SUB:
				case ADD:
				case SLL:
				case SLT:
				case SLTU:
				case XOR:
				case SRL:
				case SRA:
				case OR:
				case AND:
					set_arith_norm_sig(inst, &ctrl_sig);
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					set_arith_shift_shm_sig(inst, &ctrl_sig);
					break;
				default:
					printf("undefined instructions can't be decoded\n");
			}
	}
	return ctrl_sig;
}
