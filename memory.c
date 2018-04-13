unsigned int memory_rw(unsigned char* memory, unsigned int mem_write, unsigned int mem_type, unsigned int addr, unsigned int data) {
	// Store instruction
	// copy the rs2 data into the memory
	if (mem_write && mem_type != FN3_NONE) {
		// byte addressing?
		
		
	} else if (!mem_write && mem_type != FN3_NONE) {	// Load instruction
	} else {
		// Other instruction types
	}

