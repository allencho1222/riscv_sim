// memory type
#define BYTE	  0b00000000000000000000000011111111
#define HALF	  0b00000000000000001111111111111111
#define WORD	  0b11111111111111111111111111111111
#define BYTEU	  0b100
#define HALFU	  0b101

// alu type
#define ALU_AS	  0b000			// ADD/SUB
#define ALU_SLT	  0b010
#define ALU_SLTU  0b011
#define ALU_XOR	  0b100
#define ALU_OR	  0b110
#define ALU_AND	  0b111
#define ALU_SLL	  0b001
#define ALU_SH	  0b101			// shift left / shift right

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

#define COMP_OP(X)	((OP_MASK) & (X))
#define COMP_FN7(X)	((FN7_MASK) & (X))
#define COMP_FN3(X)	((FN3_MASK) & (X))

// RS1 mask
#define RS1_MASK  0b00000001111100000000000000000000
// RS2 mask
#define RS2_MASK  0b00000000000011111000000000000000
// RD mask
#define RD_MASK   0b00000000000000000000111110000000

// Immediate mask for extraction
#define I_IMM_MASK	0b11111111111100000000000000000000
#define S2_IMM_MASK	0b11111110000000000000000000000000 
#define S1_IMM_MASK	0b00000000000000000000111110000000 
#define SB1_IMM_MASK	0b10000000000000000000000000000000
#define SB2_IMM_MASK	0b01111110000000000000000000000000
#define SB3_IMM_MASK	0b00000000000000000000000010000000
#define SB4_IMM_MASK	0b00000000000000000000111100000000
#define U_IMM_MASK      0b11111111111111111111000000000000
#define UJ1_IMM_MASK    0b10000000000000000000000000000000
#define UJ2_IMM_MASK    0b00000000000011111111000000000000
#define UJ3_IMM_MASK    0b00000000000100000000000000000000
#define UJ4_IMM_MASK    0b01111111111000000000000000000000

#define OP_MASK	  0b00000000000000000000000001111111
#define FN7_MASK  0b11111110000000000000000000000000
#define FN3_MASK  0b00000000000000000111000000000000

// load/store memory type
#define MEM_TYPE(X) (COMP_FN3(X) >> (12))

// alu type
#define ALU_TYPE(X) (COMP_FN(X) >> (12))

#define FN3_NONE	0b11111

// get RS1, RS2, RD
// X is an instruction
#define GET_RS1(X)  (((RS1_MASK) & (X)) >> (20))
#define GET_RS2(X)  (((RS2_MASK) & (X)) >> (15))
#define GET_RD(X)   (((RD_MASK) & (X)) >> (7))
#define GET_SHM(X)  (((RS1_MASK) & (X)) >> (20))

#define GET_I_IMM(X)		((I_IMM_MASK) & (X))
#define GET_S_IMM(X)		((ST_IMM_MASK) & (X))



struct ctrl_signal { int alu_fn;
  int imm_type;
  int rs1_type;
  int rs2_type;
  int mem_type;
  int reg_write;
  int mem_write;
};

// set instruction's contron signals
void set_load_sig(struct instruction* inst);
void set_store_sig(struct instruction* inst);
void set_arith_imm_sig(struct instruction* inst);
void set_arith_norm_sig(struct instruction* inst);
void set_branch_sig(struct instruction* inst);
void set_arith_shift_shm_sig(struct instruction* inst);

// decode instructions
struct ctrl_signal decode(struct instruction* inst);
