#include "alu.h"

void print_value(signed int input1, signed int input2) {
	printf("rs1 : %08x\n", input1);
	printf("rs2 : %08x\n", input2);
}

unsigned int alu(signed int input1, signed int input2, unsigned int fn) {
	// input1 : rs1 data
	// input2 : rs2 data
	// fn : alu function
	print_value(input1, input2);
  switch (fn) {
	  case ALU_ADD:	// signed
		  return (input1) + (input2);
	  case ALU_SUB:
		  return (input1) - (input2);
	  case ALU_SLT:	// signed
		  return ((input1) < (input2)) ? 1 : 0;
	  case ALU_SLTU:	// unsigned
		  return ((unsigned int)(input1) < (unsigned int)(input2)) ? 1 : 0;
	  case ALU_AND:
		  return (input1) & (input2);
	  case ALU_XOR:
		  return (input1) ^ (input2);
	  case ALU_OR:
		  return (input1) | (input2);
	  case ALU_SLL:	// shift amount represented in register -> lower 5 bits of (input2)(rs2 data)
		  return (input1) << (31 & (input2));
	  case ALU_SEQ:
		  return ((input1) == (input2)) ? 1 : 0;
	  case ALU_SNE:
		  return ((input1) != (input2)) ? 1 : 0;
	  case ALU_SGE:
		  return ((input1) <= (input2)) ? 1 : 0;
	  case ALU_SGEU:
		  return ((unsigned int)(input1) <= (unsigned int)(input2)) ? 1 : 0;
		  /*
	  case ALU_AUIPC:
		  printf("AUIPC: input2 << 12 : %d\n", input2 << 12);
		  printf("AUIPC2: input2 << 12 & mask : %d\n", (input2 << 12) & 0b11111111111111111111000000000000);
		  unsigned int data = (input2 << 12) & 0b11111111111111111111000000000000;
		  printf("data: %0x\n", input1 + data);
		  return (input1 + ((input2 << 12) & 0b11111111111111111111000000000000));
		  */
	  case ALU_AUIPC:
		  return input1 + input2;
		  /*
	  case ALU_LUI:
		  return (input1 + ((input2) << 12) & 0b11111111111111111111000000000000);
		  */
	  case ALU_LUI:
		  return input1 + input2;
	  case ALU_SRL:
		  return (unsigned int)(input1) >> (31 & (input2));
	  case ALU_SRA:
		  return (input1) >> (31 & (input2));
	  case ALU_JAL:
		  return (input1) + ((input2) * 2);
	  case ALU_JALR:
		  return ((input1) + (input2)) & 0b11111111111111111111111111111110;
	  default:
		printf("ALU module got an error regarding ALU function\n");
		return 0;
  }
}
