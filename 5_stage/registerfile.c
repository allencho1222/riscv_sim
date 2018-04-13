struct two_reg_data register_read
	(unsigned int* register_file, unsigned int rs1, 
	 unsigned int rs2) {

	struct two_reg_data reg_data;
	reg_data.rs1_data = register_file[rs1];
	reg_data.rs2_data = register_file[rs2];

	return reg_data;
}

void register_write(unsigned int* register_file, 
		unsigned int rd, unsigned int data, unsigned int reg_write) {
	if (reg_write)
		register_file[rd] = data;
}
