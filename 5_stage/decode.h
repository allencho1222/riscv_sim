// memory type
#define BYTE	0b00000000000000000000000000000000
#define HALF	0b00000000000000000001000000000000
#define WORD	0b00000000000000000010000000000000
#define BYTEU	0b00000000000000000100000000000000
#define HALFU	0b00000000000000000101000000000000

// alu type
// ADD & SUB have same fn3 => 0b000
// SRL & SRA have same fn3 => 0b101
#define ALU_ADD	  0b1010
#define ALU_SUB	  0b1011
#define ALU_SLT	  0b010			
#define ALU_SLTU  0b011
#define ALU_XOR	  0b100
#define ALU_OR	  0b110
#define ALU_AND	  0b111
#define ALU_SLL	  0b001
#define ALU_SRL	  0b1000			// shift right
#define ALU_SRA	  0b1001		// shift right arithmetic

// immediate type
#define IMM_SB	  0b000000		// immediate in branch
#define IMM_I	  0b000010		// immediate in load, JALR, immediate alu
#define IMM_S	  0b000100		// immediate in store
#define IMM_U     0b001000
#define IMM_UJ    0b010000
#define IMM_NONE  0b100000


// register type
#define RS1	  0b0000
#define RS2	  0b0010
#define SHM	  0b0100		// shift amount
#define IMM	  0b1000	

// load/store memory type
#define MEM_TYPE(X) (COMP_FN3(X))

// alu type
#define ALU_TYPE(X) (COMP_FN(X))

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
};


// decode instructions
struct ctrl_signal decode(struct instruction* inst);
