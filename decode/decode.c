struct ctrl_signal decode(unsigned int inst) {
	switch (COMP_OP(inst) | COMP_FN3(inst)) {
		case LB:
		case LH:
		case LW:
		case LBU:
		case LHU:
			set_load_sig(inst);
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
			set_arith_imm_sig(inst);
			break;
		case BEQ:
		case BNE:
		case BLT:
		case BGE:
		case BLTU:
		case BGEU:
			set_branch_sig(inst);
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
					set_arith_norm_sig(inst);
					break;
				case SLLI:
				case SRLI:
				case SRAI:
					set_arith_shift_imm_sig(inst);
					break;
				case default:
					printf("undefined instructions can't be decoded\n");
			}
	}
	return inst->ctrl_sig;
}
