#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"


// forward declarations
void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_auipc(Instruction, Processor *);
void execute_lui(Instruction, Processor *);


void execute_instruction(Instruction instruction,Processor *processor,Byte *memory) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  switch(instruction.opcode) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x33:
      execute_rtype(instruction, processor);
      processor -> PC += 4;
      break;
    case 0x13:
      execute_itype_except_load(instruction, processor);
      processor -> PC += 4;
      break;
    case 0x73:
      execute_ecall(processor, memory);
      processor -> PC += 4;
      break;
    case 0x63:
      execute_branch(instruction, processor);
      processor -> PC += 4;
      break;
    case 0x6F:
      execute_jal(instruction, processor);
      processor -> PC += 4;
      break;
    case 0x23:
      execute_store(instruction, processor, memory);
      processor -> PC += 4;
      break;
    case 0x03:
      execute_load(instruction, processor, memory);
      processor -> PC += 4;
      break;
    case 0x37:
      execute_lui(instruction, processor);
      processor -> PC +=4;
      break;
    case 0x43:
      execute_jalr(instruction, processor);
      processor -> PC += 4;
      break;
    case 0x11:
      execute_auipc(instruction, processor);
      processor -> PC += 4;
      break;
    default: // undefined opcode
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_rtype(Instruction instruction, Processor *processor) {
  switch(instruction.rtype.funct3){ // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
           switch (instruction.rtype.funct7) {
               case 0x0:
                   processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] + (int)processor->R[instruction.rtype.rs2];
                   break;
               case 0x1:
                   processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] * (int)processor->R[instruction.rtype.rs2];
                   break;
               case 0x20:
                   processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] - (int)processor->R[instruction.rtype.rs2];
                   break;
               default:
                   handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x1:
           switch (instruction.rtype.funct7) {
               case 0x0:
                  processor->R[instruction.rtype.rd] = (unsigned)processor->R[instruction.rtype.rs1] << (int)processor->R[instruction.rtype.rs2];
                  break;
               case 0x1:
                  processor->R[instruction.rtype.rd] = (sDouble)processor->R[instruction.rtype.rs1] * (sDouble)(processor->R[instruction.rtype.rs2]) >> 32;
                  break;
               default:
                  handle_invalid_instruction(instruction);
                  break;
           }
           break;
       case 0x2:
           if((processor->R[instruction.rtype.rs1] < processor->R[instruction.rtype.rs2])){
             processor->R[instruction.rtype.rd] = 1;
           }else{
             processor->R[instruction.rtype.rd] = 0;
           }
           break;
       case 0x4:
           switch (instruction.rtype.funct7) {
               case 0x0:
                  processor->R[instruction.rtype.rd] = (unsigned)processor->R[instruction.rtype.rs1] ^ (unsigned)processor->R[instruction.rtype.rs2];
                  break;
               case 0x1:
                  processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] / (int)processor->R[instruction.rtype.rs2];
                  break;
               default:
                  handle_invalid_instruction(instruction);
                  break;
           }
           break;
       case 0x5:
           switch (instruction.rtype.funct7) {
               case 0x0:
                  processor->R[instruction.rtype.rd] = (unsigned)processor->R[instruction.rtype.rs1] >> (int)processor->R[instruction.rtype.rs2];
                  break;
               case 0x20:
                  processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] >> (int)processor->R[instruction.rtype.rs2];
                  break;
               default:
                  handle_invalid_instruction(instruction);
                  break;
           }
           break;
       case 0x6:
           switch (instruction.rtype.funct7) {
               case 0x0:
                  processor->R[instruction.rtype.rd] = (unsigned)processor->R[instruction.rtype.rs1] | (unsigned)processor->R[instruction.rtype.rs2];
                  break;
               case 0x1:
                  processor->R[instruction.rtype.rd] = (int)processor->R[instruction.rtype.rs1] % (int)processor->R[instruction.rtype.rs2];
                  break;
               default:
                  handle_invalid_instruction(instruction);
                  break;
           }
           break;
       case 0x7:
           processor->R[instruction.rtype.rd] = (unsigned)processor->R[instruction.rtype.rs1] & (unsigned)processor->R[instruction.rtype.rs2];
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void execute_itype_except_load(Instruction instruction, Processor *processor) {
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
          processor->R[instruction.itype.rd] = (int)processor->R[instruction.itype.rs1] + (int)bitSigner(instruction.itype.imm, 12);
          break;
       case 0x1:
          processor->R[instruction.itype.rd] = (unsigned)processor->R[instruction.itype.rs1] << (int)instruction.itype.imm;
          break;
       case 0x2:
          if((int)processor->R[instruction.itype.rs1] < (int)bitSigner(instruction.itype.imm, 12)){
            processor->R[instruction.itype.rd] = 1;
          }else{
            processor->R[instruction.itype.rd] = 0;
          }
          break;
       case 0x4:
          processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] ^ (unsigned)bitSigner(instruction.itype.imm, 12);
          break;
       case 0x5:
          switch(instruction.itype.imm>>5){
              case 0x0:
                  processor->R[instruction.itype.rd] = (unsigned)processor->R[instruction.itype.rs1] >> (int)processor->R[instruction.itype.imm];
                  break;
              case 0x20:
                  processor->R[instruction.itype.rd] = (int)processor->R[instruction.itype.rs1] >> (int)instruction.itype.imm;
                  break;
              default:
                  handle_invalid_instruction(instruction);
                  break;
          }
           break;
       case 0x6:
          processor->R[instruction.itype.rd] = (unsigned)processor->R[instruction.itype.rs1] | (unsigned)bitSigner(instruction.itype.imm, 12);
          break;
       case 0x7:
          processor->R[instruction.itype.rd] = (unsigned)processor->R[instruction.itype.rs1] & (unsigned)bitSigner(instruction.itype.imm, 12);
          break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void execute_ecall(Processor *p, Byte *memory) {
  int aux;
  switch(p->R[10]) { // What do we switch on?
    /* YOUR CODE HERE */
    case 1:
      printf("%d", p->R[11]);
      break;
    case 4:
      for(aux=p->R[11]; aux<MEMORY_SPACE && load(memory, aux, LENGTH_BYTE, 1); aux++){
        printf("%c", load(memory, aux, LENGTH_BYTE, 1));
      }
      break;
    case 10:
      printf("exiting the simulator...\n");
      break;
    case 11:
      printf("%c", p->R[11]);
      break;
    default: // undefined ecall
      printf("Illegal ecall number %d\n", -1); // What stores the ecall arg?
      exit(-1);
      break;
  }
}


void execute_branch(Instruction instruction, Processor *processor) {
  /* Remember that the immediate portion of branches
     is counting half-words, so make sure to account for that. */
     
  switch(instruction.sbtype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      if ((int) processor->R[instruction.sbtype.rs1] == (int) processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
      }else{
                processor->PC += 4;
      }break;
    case 0x1:
      if ((int) processor->R[instruction.sbtype.rs1] != (int) processor->R[instruction.sbtype.rs2]){
                processor->PC += get_branch_offset(instruction);
      }else{
                processor->PC += 4;
      }break;
    default:
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1]+bitSigner(instruction.itype.imm, 12), LENGTH_BYTE, 0);
      break;
    case 0x1:
      processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1]+bitSigner(instruction.itype.imm, 12), LENGTH_HALF_WORD, 0);
      break;
    case 0x2:
      processor->R[instruction.itype.rd] = load(memory, processor->R[instruction.itype.rs1]+bitSigner(instruction.itype.imm, 12), LENGTH_WORD, 0);
      break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}


void execute_store(Instruction instruction, Processor *processor, Byte *memory) {
  switch(instruction.stype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
      store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_BYTE, processor->R[instruction.stype.rs2], 0);
      break;
    case 0x1:
      store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_HALF_WORD, processor->R[instruction.stype.rs2], 0);
      break;
    case 0x2:
      store(memory, processor->R[instruction.stype.rs1] + get_store_offset(instruction), LENGTH_WORD, processor->R[instruction.stype.rs2], 0);
      break;
    default:
      handle_invalid_instruction(instruction);
      exit(-1);
      break;
  }
}


void execute_jalr(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */ 
}


void execute_jal(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  int voPC;
  voPC = processor->PC + get_jump_offset(instruction);
  processor->R[instruction.ujtype.rd] = processor->PC + 4;
  processor->PC = voPC;
}

void execute_auipc(Instruction instruction, Processor *processor) {
  /* YOUR CODE HERE */
  processor->R[instruction.utype.rd] = processor->PC +4;
}


void execute_lui(Instruction instruction, Processor *processor) {
  /* no critiques mi variable :/*/
  processor->R[instruction.utype.rd] = instruction.utype.imm << 12;
}


/* Checks that the address is aligned correctly */
int check(Address address, Alignment alignment) {
  if (address > 0 && address < MEMORY_SPACE) {
    // byte align
    if (alignment == LENGTH_BYTE) return 1;
    // half align
    if (alignment == LENGTH_HALF_WORD) return ((address % 2) == 0);
    // word align
    if (alignment == LENGTH_WORD) return ((address % 4) == 0);
  }
  return 0;
}


void store(Byte *memory, Address address, Alignment alignment, Word value, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_write(address);
  }
}


Word load(Byte *memory, Address address, Alignment alignment, int check_align) {
  if ((check_align && !check(address,alignment)) || (address >= MEMORY_SPACE)) {
    handle_invalid_read(address);
  } return 0;
}
