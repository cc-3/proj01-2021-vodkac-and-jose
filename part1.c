#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

// forward declarations
void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void write_rtype(Instruction);  //check dentro de decode
void write_itype_except_load(Instruction);  //check dentro de decode
void write_load(Instruction);  //check dentro de decode
void write_store(Instruction);  //check dentro de decode
void write_branch(Instruction);  //check dentro de decode
void write_auipc(Instruction);  // aun falta nose que caso es ?
void write_lui(Instruction); // check dentro de decode
void write_jalr(Instruction);  // aun falta nose que caso es ?
void write_jal(Instruction);  //check dentro de decode
void write_ecall(Instruction); //check dentro de decode

//falta implementar las de arriba
void decode_instruction(Instruction instruction) {
  /* YOUR CODE HERE: COMPLETE THE SWITCH STATEMENTS */
  switch(instruction.opcode) { // What do we switch on?
    /* YOUR CODE HERE */
        case 0x33:
            write_rtype(instruction);
            break;
        case 0x03:
            write_load(instruction);
            break;
        case 0x13:
            write_itype_except_load(instruction);
            break;
        case 0x73:
            write_ecall(instruction);
            break;
        case 0x23:
            write_store(instruction);
            break;
        case 0x63:
            write_branch(instruction);
            break;
        case 0x37:
            write_lui(instruction);
            break;
        case 0x6f:
            write_jal(instruction);
            break;
        case 0x67:
            write_jalr(instruction);
            break;
        case 0x17:
            write_auipc(instruction);
            break;
    default: // undefined opcode
      handle_invalid_instruction(instruction);
      break;
  }
}
//todo corregido y sin problemas
void write_rtype(Instruction instruction) {
  switch(instruction.rtype.funct3){ // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
           switch (instruction.rtype.funct7) {
               case 0x0:
                   print_rtype("add", instruction);
                   break;
               case 0x1:
                   print_rtype("mul", instruction);
                   break;
               case 0x20:
                   print_rtype("sub", instruction);
                   break;
               default:
                   handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x1:
           switch (instruction.rtype.funct7) {
               case 0x0:
               print_rtype("sll", instruction);
               break;
               case 0x1:
               print_rtype("mulh", instruction);
               break;
               default:
               handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x2:
           print_rtype("slt", instruction);
           break;
       case 0x4:
           switch (instruction.rtype.funct7) {
               case 0x0:
               print_rtype("xor", instruction);
               break;
               case 0x1:
               print_rtype("div", instruction);
               break;
               default:
               handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x5:
           switch (instruction.rtype.funct7) {
               case 0x0:
               print_rtype("srl", instruction);
               break;
               case 0x20:
               print_rtype("sra", instruction);
               break;
               default:
               handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x6:
           switch (instruction.rtype.funct7) {
               case 0x0:
               print_rtype("or", instruction);
               break;
               case 0x1:
               print_rtype("rem", instruction);
               break;
               default:
               handle_invalid_instruction(instruction);
               break;
           }
           break;
       case 0x7:
           print_rtype("and", instruction);
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}

void write_itype_except_load(Instruction instruction) {
  switch(instruction.itype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
           print_itype_except_load("addi", instruction, instruction.itype.imm);
           break;
       case 0x1:
           print_itype_except_load("slli", instruction, instruction.itype.imm);
           break;
       case 0x2:
           print_itype_except_load("slti", instruction, instruction.itype.imm);
           break;
       case 0x4:
           print_itype_except_load("xori", instruction, instruction.itype.imm);
           break;
       case 0x5:
            switch(instruction.itype.imm>>10){
               case 0x0:
                   print_itype_except_load("srli", instruction, instruction.itype.imm & 0x1F);
                   break;
               case 0x1:
                   print_itype_except_load("srai", instruction, instruction.itype.imm & 0x1F);
                   break;
               default:
                   handle_invalid_instruction(instruction);
                   break;
           }
           break;
       case 0x6:
           print_itype_except_load("ori", instruction, instruction.itype.imm);
           break;
       case 0x7:
           print_itype_except_load("andi", instruction, instruction.itype.imm);
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}
//todo corregido y compledo
void write_load(Instruction instruction) {
  switch(instruction.itype.funct3){ // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
           print_load("lb", instruction);
           break;
       case 0x1:
           print_load("lh", instruction);
           break;
       case 0x2:
           print_load("lw", instruction);
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}
//todo corregido y sin problemas
void write_store(Instruction instruction) {
  switch(instruction.stype.funct3){ // What do we switch on?
    /* YOUR CODE HERE */
    case 0x0:
           print_store("sb", instruction);
           break;
       case 0x1:
           print_store("sh", instruction);
           break;
       case 0x2:
           print_store("sw", instruction);
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}
//todo completado y corregido
void write_branch(Instruction instruction) {
  switch(instruction.sbtype.funct3) { // What do we switch on?
    /* YOUR CODE HERE */
      case 0x0:
           print_branch("beq", instruction);
           break;
       case 0x1:
           print_branch("bne", instruction);
           break;
    default:
      handle_invalid_instruction(instruction);
      break;
  }
}

/* For the writes, probably a good idea to take a look at utils.h */

void write_auipc(Instruction instruction) {
  /* YOUR CODE HERE */
  printf(AUIPC_FORMAT, instruction.utype.rd, (unsigned)instruction.utype.imm);
}

void write_lui(Instruction instruction) {
  /* YOUR CODE HERE */
   unsigned int rd = instruction.utype.rd;
   unsigned int imm = instruction.utype.imm;
   printf("lui\tx%d, %d\n", rd, imm);
}

void write_jalr(Instruction instruction) {
  /* YOUR CODE HERE */
  printf(JALR_FORMAT, (unsigned int)instruction.itype.rd, (unsigned int)instruction.itype.rs1, (unsigned int)bitSigner(instruction.itype.imm, 12));
}

void write_jal(Instruction instruction) {
  /* YOUR CODE HERE */
int offset = get_jump_offset(instruction);
printf("jal\tx%d, %d\n", instruction.ujtype.rd, offset);
}

void write_ecall(Instruction instruction) {
  /* YOUR CODE HERE */
   printf("ecall\n");
}

void print_rtype(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
   unsigned int rd = instruction.rtype.rd;
   unsigned int rs1 = instruction.rtype.rs1;
   unsigned int rs2 = instruction.rtype.rs2;
   printf("%s\tx%d, x%d, x%d\n", name, rd, rs1, rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
  /* YOUR CODE HERE */
   unsigned int rd = instruction.itype.rd;
   unsigned int rs1 = instruction.itype.rs1;
   printf(ITYPE_FORMAT, name, rd, rs1, bitSigner(imm, 12));
}

void print_load(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
      unsigned int rs1 = instruction.itype.rs1;
      unsigned int rd = instruction.itype.rd;
      int imm = instruction.itype.imm;
      int aux = bitSigner(imm, 12);
      printf("%s\tx%d, %d(x%d)\n", name, rd, aux , rs1);
}

void print_store(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
    unsigned int rs1 = instruction.stype.rs1;
    unsigned int rs2 = instruction.stype.rs2;
    int imm = get_store_offset(instruction);
    printf(MEM_FORMAT, name, rs2, imm, rs1);
}

void print_branch(char *name, Instruction instruction) {
  /* YOUR CODE HERE */
   unsigned int rs1 = instruction.sbtype.rs1;
   unsigned int rs2 = instruction.sbtype.rs2;
   int offset = get_branch_offset(instruction);
   printf("%s\tx%d, x%d, %d\n", name, rs1, rs2, offset);
}
