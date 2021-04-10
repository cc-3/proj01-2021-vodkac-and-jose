#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int extendMethod(unsigned int num, int n1, int n2) {
    int aux = ~(~0<<(n2-n1+1));
    return (num>>n1)&aux;
}


//sign extends a bitfield with given size
/* You may find implementing this function helpful */
int bitSigner(unsigned int field, unsigned int size) {
  /* YOUR CODE HERE */
  unsigned int extendSign;
  unsigned int ext = 0xFFFFFFFF << size;
  if((field & (1<<(size-1))) != 0){
    extendSign = field | ext;
  }else{
    extendSign = field & ~ext;
  }
  return extendSign;
}


/* Remember that the offsets should return the offset in BYTES */

int get_branch_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int bo1 = instruction.sbtype.imm7;
  unsigned int bo2 = instruction.sbtype.imm5;
  unsigned int bo3 = extendMethod(bo1, 6, 6);
  unsigned int bo4 = extendMethod(bo2, 0, 0);
  unsigned int bo5 = (bo3<<1)|bo4;
  unsigned int bo6 = extendMethod(bo1, 0, 5);
  unsigned int bo7 = (bo5<<6)|bo6;
  unsigned int bo8 = extendMethod(bo2,1,4);
  unsigned int bo9 = (bo7<<4)|bo8;
  return bitSigner((bo9<<1),13);
}


int get_jump_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  unsigned int imm = instruction.ujtype.imm;
  unsigned int aux1 = extendMethod(imm, 0, 7);
  unsigned int aux2 = extendMethod(imm, 8, 8);
  unsigned int aux3 = extendMethod(imm, 9, 18);
  unsigned int aux4 = extendMethod(imm, 19, 19);
  unsigned int respuesta = ((((((aux4 << 8)|aux1)<<1)|aux2)<<10)|aux3)<< 1;
  return bitSigner(respuesta, 21);
}


int get_store_offset(Instruction instruction) {
  /* YOUR CODE HERE */
  return bitSigner(((instruction.stype.imm7 << 5)|(instruction.stype.imm5)), 12);
}


void handle_invalid_instruction(Instruction instruction) {
  printf("Invalid Instruction: 0x%08x\n", instruction.bits);
}


void handle_invalid_read(Address address) {
  printf("Bad Read. Address: 0x%08x\n", address);
  exit(-1);
}


void handle_invalid_write(Address address) {
  printf("Bad Write. Address: 0x%08x\n", address);
  exit(-1);
}

