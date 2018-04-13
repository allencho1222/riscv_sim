#include "decode.h"

void set_load_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
  inst->ctrl_sig.alu_fn = ALU_ADD;
  inst->ctrl_sig.imm_type = IMM_I;
  inst->ctrl_sig.rs1_type = RS1;
  inst->ctrl_sig.rs2_type = IMM;
  inst->ctrl_sig.mem_type = MEM_TYPE(inst->inst);
  inst->reg_write = 1;
  inst->mem_write = 0;
  inst->mem_read = 1;
} 

void set_store_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
  inst->ctrl_sig.alu_fn = ALU_ADD;
  inst->ctrl_sig.imm_type = IMM_S;
  inst->ctrl_sig.rs1_type = RS1;
  inst->ctrl_sig.rs2_type = IMM;
  inst->ctrl_sig.mem_type = MEM_TYPE(inst->inst);
  inst->reg_write = 0;
  inst->mem_write = 1;
  inst->mem_read = 0;
}

void set_arith_imm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst->inst);
	if (alu_type == 0b101) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else if (alu_type == 0b000) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SUB;
		} else {
			alu_type = ALU_ADD;
		}
	} else {}
	inst->ctrl_sig.alu_fn = alu_type;
	inst->ctrl_sig.imm_type = IMM_I;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = IMM;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
}

void set_branch_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	// TODO : branch alu type
	inst->ctrl_sig.alu_fn = ALU_TYPE(inst->inst);
	inst->ctrl_sig.imm_type = IMM_SB;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = RS2;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 0;
	inst->mem_write = 0;
	inst->mem_read = 0;
}

void set_arith_norm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst->inst);
	if (alu_type == 0b101) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else if (alu_type == 0b000) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SUB;
		} else {
			alu_type = ALU_ADD;
		}
	} else {}
	inst->ctrl_sig.alu_fn = alu_type;
	inst->ctrl_sig.imm_type = IMM_NONE;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = RS2;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
	inst->mem_read = 0;
}

void set_arith_shift_shm_sig(unsigned int inst, struct ctrl_signal *ctrl_sig) {
	int alu_type = ALU_TYPE(inst->inst);
	if (alu_type == 0b101) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SRL;
		} else {
			alu_type = ALU_SRA;
		}
	} else if (alu_type == 0b000) {
		if (COMP_FN7(inst->inst) == 0b0000000) {
			alu_type = ALU_SUB;
		} else {
			alu_type = ALU_ADD;
		}
	} else {}
	inst->ctrl_sig.alu_fn = alu_type;
	inst->ctrl_sig.imm_type = IMM_NONE
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = SHM
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
	inst->mem_read = 0;
}

struct ctrl_signal decode(unsigned int inst) {
	struct ctrl_signal ctrl_sig;
	switch (COMP_OP(inst) | COMP_FN3(inst)) {
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
			set_store_sig(inst);
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
		case default:
			switch (COMP_OP(inst) | COMP_FN3(inst) | COMP_FN7(inst)) {
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
					set_arith_shift_imm_sig(inst, &ctrl_sig);
					break;
				case default:
					printf("undefined instructions can't be decoded\n");
			}
	}
	return ctrl_sig;
}
