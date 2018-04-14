#include "alu.h"

unsigned int alu(signed int input1, signed int input2, unsigned int fn) {
	// input1 : rs1 data
	// input2 : rs2 data
	// fn : alu function
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
	  case ALU_AUIPC:
		  return (input1 + ((input2) << 12) & 0b11111111111111111111000000000000);
	  case LUI:
		  return (input1 + ((input2) << 12) & 0b11111111111111111111000000000000);
	  case SRLI:	// right shift on unsigned value -> logical shift
		  return (unsigned int)(input1) >> (input2);
	  case SRL:
		  return (unsigned int)(input1) >> (31 & (input2));
	  case SRAI:	// right shift on singed value -> arithmetic shift
		  return (input1) >> (input2);
	  case SRA:
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
