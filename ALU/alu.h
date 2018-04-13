#include alu_fn.h

struct alu_output {
  unsigned int  result;
  int           compare;
};

alu_output alu(unsigned int input1, unsigned int input2, alu_func fn);
