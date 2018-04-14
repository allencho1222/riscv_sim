#ifndef DECODE_H
#define DECODE_H
#include "../util/maskop.h"
#include "../instruction/instructions.h"
#include <stdio.h>
#include <string.h>

// memory type
#define BYTE	0b00000000000000000000000000000000
#define HALF	0b00000000000000000001000000000000
#define WORD	0b00000000000000000010000000000000
#define BYTEU	0b00000000000000000100000000000000
#define HALFU	0b00000000000000000101000000000000

// alu type
// ADD & SUB have same fn3 => 0b000
// SRL & SRA have same fn3 => 0b101
#define ALU_ADD	  0b000
#define ALU_SUB	  0b01000
#define ALU_SLT	  0b010
#define ALU_SLTU  0b011
#define ALU_XOR	  0b100
#define ALU_OR	  0b110
#define ALU_AND	  0b111
#define ALU_SLL	  0b001
#define ALU_SRL	  0b101			// shift right
#define ALU_SRA	  0b01001		// shift right arithmetic
#define ALU_SEQ	  0b01010		// for BRE
#define ALU_SNE	  0b01011		// for BNE
#define ALU_SGE	  0b01100		// for BGE
#define ALU_SGEU  0b01101		// for BGEU
#define ALU_LUI	  0b01110
#define ALU_AUIPC 0b01111
#define ALU_JAL	  0b010000
#define ALU_JALR  0b010001

#define BR_TYPE(X)	(GET_FN3(X) >> (12))

// immediate type
#define IMM_SB	  0b000000		// immediate in branch
#define IMM_I	  0b000010		// immediate in load, JALR, immediate alu
#define IMM_S	  0b000100		// immediate in store
#define IMM_U     0b001000
#define IMM_UJ    0b010000
#define IMM_NONE  0b100000


// register type
#define RS1	  0b0000
#define RS2	  0b0001
#define SHM	  0b0010		// shift amount
#define IMM	  0b0011	
#define PC	  0b0100
#define ZERO	  0b0101

// load/store memory type
#define MEM_TYPE(X) (GET_FN3(X) >> (12))

// alu type
#define ALU_TYPE(X) (GET_FN3(X) >> (12))

#define FN3_NONE	0b11111


struct ctrl_signal { 
  int alu_fn;
  int imm_type;		// R, I, S, SB, U, UJ
  int rs1_type;		// RS1, RS2, IMM, SHM, NONE
  int rs2_type;
  int mem_type;		// BYTE, HALF, WORD, BYTEU, HALFU
  int reg_write;	// reg write or not
  int mem_write;	// memory write or not
  int mem_read;		// memory read or not
  int is_branch;
  int is_jalr;
  int is_jal;
  int is_aui;
};


// decode instructions
struct ctrl_signal decode(unsigned int inst, char *inst_str);
#endif
