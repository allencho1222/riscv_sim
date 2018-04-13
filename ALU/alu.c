alu_output alu(unsigned int input1, unsigned int input2, alu_func fn) {
  struct alu_output alu_out = {0, 0};

  switch (fn) {
    case ALU_ADD:
      alu_out.result = input1 + input2;
      break;
    case ALU_SUB:
      alu_out.result = input1 - input2;
      break;
    case ALU_SNE:
      alu_out.result = (input1 != input2) ? 1 : 0;
      break;
    case ALU_SEQ:
      alu_out.result = (input1 == input2) ? 1 : 0;
      break;
    case ALU_SLT:
      alu_out.result = (input1 < input2) ? 1 : 0;
      break;
    case ALU_SGE:
      alu_out.result = (input1 > input2) ? 1 : 0;
      break;
    case ALU_SL:
      alu_out.result = input1 << input2;  // input2(rs2)'s lower 5 bits
      break;
    case ALU_SR:
      alu_out.result = input1 >> input2;  // same as ALU_SL
      break;
    case ALU_SRA:
      alu_out.result = (signed int) input1 >> input2; // same as ALU_SL
      break;
    case ALU_XOR:
      alu_out.result = input1 ^ input2;
      break;
    case ALU_OR:
      alu_out.result = input1 | input2;
      break;
    case ALU_AND:
      alu_out.result = input1 & input2;
      break;
    case default:
      printf("ALU module got an error regarding ALU function\n");
      break;
  }

  return alu_out;
}
