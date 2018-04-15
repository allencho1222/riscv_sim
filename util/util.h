#ifndef UTIL_H
#define UTIL_H
#include <stdio.h>
#include "../5_stage/decode.h"

struct display_data {
	unsigned char *memory;
	unsigned int *reg_file;
	unsigned int *pc;
	unsigned int *binary_inst;
	char *inst;
        struct ctrl_signal *ctrl_sig;
        unsigned int *loaded_data;
        unsigned int *wr_data;
        unsigned int *addr;
};

void program_head(void);
void program_output(struct display_data data);
#endif
