#ifndef MASKOP_H
#define MASKOP_H
// OP, FN7, FN3 mask
#define OP_MASK	  0b00000000000000000000000001111111
#define FN7_MASK  0b11111110000000000000000000000000
#define FN3_MASK  0b00000000000000000111000000000000

// get OP, FN7, FN3
#define GET_OP(X)	((OP_MASK) & (X))
#define GET_FN7(X)	((FN7_MASK) & (X))
#define GET_FN3(X)	((FN3_MASK) & (X))

// RS1 mask
#define RS2_MASK  0b00000001111100000000000000000000
// RS2 mask
#define RS1_MASK  0b00000000000011111000000000000000
// RD mask
#define RD_MASK   0b00000000000000000000111110000000

// Immediate mask for extraction
#define I_IMM_MASK	0b11111111111100000000000000000000
#define S2_IMM_MASK	0b11111110000000000000000000000000 
#define S1_IMM_MASK	0b00000000000000000000111110000000 
#define SB1_IMM_MASK	0b10000000000000000000000000000000
#define SB2_IMM_MASK	0b01111110000000000000000000000000
#define SB3_IMM_MASK	0b00000000000000000000000010000000
#define SB4_IMM_MASK	0b00000000000000000000111110000000
#define U_IMM_MASK      0b11111111111111111111000000000000
#define UJ1_IMM_MASK    0b10000000000000000000000000000000
#define UJ2_IMM_MASK    0b00000000000011111111000000000000
#define UJ3_IMM_MASK    0b00000000000100000000000000000000
#define UJ4_IMM_MASK    0b01111111111000000000000000000000

// get RS1, RS2, RD
// X is an instruction
#define GET_RS1(X)  (((RS1_MASK) & (X)) >> (15))
#define GET_RS2(X)  (((RS2_MASK) & (X)) >> (20))
#define GET_RD(X)   (((RD_MASK) & (X)) >> (7))
#define GET_SHM(X)  (((RS2_MASK) & (X)) >> (20))

// get immediate operand
#define GET_I_IMM(X)	(((I_IMM_MASK) & (X)) >> (20))
#define GET_S_IMM(X)	(((((S1_IMM_MASK) & (X)) << (13)) | (((S2_IMM_MASK) & (X)))) >> (20))
#define GET_SB_IMM(X)	(((((SB4_IMM_MASK) & (X)) << (12)) | (((SB2_IMM_MASK) & (X)) >> (1)) |	\
			(((SB3_IMM_MASK) & (X)) << (23)) | (((SB1_IMM_MASK) & (X)))) >> (20))
//#define GET_U_IMM(X)	(((U_IMM_MASK) & (X)) >> (12))
#define GET_U_IMM(X)	(((U_IMM_MASK) & (X)) )
#define GET_UJ_IMM(X)	(((((UJ4_IMM_MASK) & (X)) >> (9)) | (((UJ3_IMM_MASK) & (X)) << (2)) | \
			(((UJ2_IMM_MASK) & (X)) << (11)) | (((UJ1_IMM_MASK) & (X)))) >> (12))

// sign extension
#define SIGN_EXT_I(X)	((((X) >> (11)) == 0) ? (X) : ((-1) ^ (0xFFF) | (X)))
#define SIGN_EXT_S(X)	((((X) >> (11)) == 0) ? (X) : ((-1) ^ (0xFFF) | (X)))
#define SIGN_EXT_SB(X)	((((X) >> (11)) == 0) ? (X) : ((-1) ^ (0xFFF) | (X)))
#define SIGN_EXT_U(X)	((((X) >> (19)) == 0) ? (X) : ((-1) ^ (0xFFFFF) | (X)))
#define SIGN_EXT_UJ(X)	((((X) >> (19)) == 0) ? (X) : ((-1) ^ (0xFFFFF) | (X)))
#endif
