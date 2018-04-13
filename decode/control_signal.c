void set_load_sig(struct instruction* inst) {
  inst->ctrl_sig.alu_fn = ALU_AS;
  inst->ctrl_sig.imm_type = IMM_I;
  inst->ctrl_sig.rs1_type = RS1;
  inst->ctrl_sig.rs2_type = IMM;
  inst->ctrl_sig.mem_type = MEM_TYPE(inst->inst);
  inst->reg_write = 1;
  inst->mem_write = 0;
} 

void set_store_sig(struct instruction* inst) {
  inst->ctrl_sig.alu_fn = ALU_AS;
  inst->ctrl_sig.imm_type = IMM_S;
  inst->ctrl_sig.rs1_type = RS1;
  inst->ctrl_sig.rs2_type = IMM;
  inst->ctrl_sig.mem_type = MEM_TYPE(inst->inst);
  inst->reg_write = 0;
  inst->mem_write = 1;
}

void set_arith_imm_sig(struct instruction* inst) {
	inst->ctrl_sig.alu_fn = ALU_TYPE(inst->inst);
	inst->ctrl_sig.imm_type = IMM_I;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = IMM;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
}

void set_branch_sig(struct instruction* inst) {
	inst->ctrl_sig.alu_fn = ALU_TYPE(inst->inst);
	inst->ctrl_sig.imm_type = IMM_BR;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = RS2;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 0;
	inst->mem_write = 0;
}

void set_arith_norm_sig(struct instruction* inst) {
	inst->ctrl_sig.alu_fn = ALU_TYPE(inst->inst);
	inst->ctrl_sig.imm_type = IMM_NONE;
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = RS2;
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
}

void set_arith_shift_shm_sig(struct instruction* inst) {
	inst->ctrl_sig.alu_fn = ALU_TYPE(inst->inst);
	inst->ctrl_sig.imm_type = IMM_NONE
	inst->ctrl_sig.rs1_type = RS1;
	inst->ctrl_sig.rs2_type = SHM
	inst->ctrl_sig.mem_type = FN3_NONE;
  	inst->reg_write = 1;
	inst->mem_write = 0;
}
