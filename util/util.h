#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>

struct display_data {
	unsigned char *memory;
	unsigned int *reg_file;
	unsigned int *pc;
	unsigned int *binary_inst;
	char *inst;
};

void program_head(void);
void program_output(struct display_data data);
#endif
