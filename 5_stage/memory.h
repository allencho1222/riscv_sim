#ifndef MEMORY_H
#define MEMORY_H
#include <stdio.h>
#include <string.h>
#include "decode.h"

unsigned int memory_rw(unsigned char* memory, unsigned int mem_write, unsigned int mem_read, unsigned int mem_type, unsigned int addr, unsigned int data);
#endif
