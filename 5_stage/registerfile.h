#ifndef REGISTERFILE_H
#define REGISTERFILE_H
struct two_reg_data {
	unsigned int rs1_data;
	unsigned int rs2_data;
};

struct two_reg_data register_read(unsigned int *register_file,
		unsigned int rs1, unsigned int rs2);
void register_write(unsigned int *register_file, unsigned int rd,
		unsigned int data, unsigned int reg_write);
#endif
