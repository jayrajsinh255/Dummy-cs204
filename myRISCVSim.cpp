
/* 

The project is developed as part of Computer Architecture class
Project Name: Functional Simulator for subset of RISCV Processor

Developer's Name:
Developer's Email id:
Date: 

*/


/* myRISCVSim.cpp
   Purpose of this file: implementation file for myRISCVSim
*/
#include "builtin_funcs.h"
#include"self_defined_funcs_and_classes.h"
// #include "RegisterFile.h"
// #include "Control_unit.h"
#include "global_variables.h"
using namespace std;

//Register file
// static unsigned int X[32];
//flags
//memory
// static unsigned char MEM[4000];


//intermediate datapath and control path signals


/*function prototypes*/
void fetch();
void decode();

void run_riscvsim() {
  while(1) {
    fetch();
    decode();
    // execute();
    // mem();
    // write_back();
    break;
  }
}

// it is used to set the reset values
//reset all registers and memory content to 0
void reset_proc() {
  //set PC to zero
    PC=0;
    mem.clear();
    for (int i = 0; i < 32; i++) {
        registerFile.set_register(i,0);
        if (i == 2) {
            // x[i] = 0x7FFFFFF0; // sp
                registerFile.set_register(i, strtol("0x7FFFFFF0", NULL, 16)); // sp
            
        }
        else if (i == 3) {
            // x[i] = 0x10000000; // gp
            registerFile.set_register(i,strtol("0x10000000", NULL, 16)); // gp
        }
    }
    
}

//load_program_memory reads the input memory, and pupulates the instruction 
// memory
void load_program_memory(char *file_name) {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while(fscanf(fp, "%x %x", &address, &instruction) != EOF) {
    mem[(unsigned int) address]=(unsigned int)instruction;
    // printf("%x %u\n",address,mem[(unsigned int) address]);//  
  }
  fclose(fp);
}

//writes the data memory in "data_out.mem" file
// void write_data_memory() {
//   FILE *fp;
//   unsigned int i;
//   fp = fopen("data_out.mem", "w");
//   if(fp == NULL) {
//     printf("Error opening dataout.mem file for writing\n");
//     return;
//   }
  
//   for(i=0; i < 4000; i = i+4){
//     fprintf(fp, "%x %x\n", i, read_word(MEM, i));
//   }
//   fclose(fp);
// }

// //should be called when instruction is swi_exit
// void swi_exit() {
//   write_data_memory();
//   exit(0);
// }


// //reads from the instruction memory and updates the instruction register
void fetch() {
    unsigned int instruct_dec=mem[(unsigned int )PC];
    string instruction=dec2bin(instruct_dec);
    if_de_rest.instruction=instruction;
}
// //reads the instruction register, reads operand1, operand2 fromo register file, decides the operation to be performed in execute stage
void decode(){
    // getting destination register
    string rds=if_de_rest.instruction.substr(20,5);
    int rd=(int)unsgn_binaryToDecimal(rds);
    // getting source register 1
    string rs1s=if_de_rest.instruction.substr(12,5);
    int rs1=unsgn_binaryToDecimal(rs1s);
    //getting source register 2
    string rs2s=if_de_rest.instruction.substr(7,5);
    int rs2=unsgn_binaryToDecimal(rs2s);
    int imm=immediate(if_de_rest.instruction);
    //setting the controls
    mycontrol_unit.set_instruction(if_de_rest.instruction);
    mycontrol_unit.build_control();

    de_ex_rest.rd=rd;
    de_ex_rest.A=registerFile.get_register(rs1);
    de_ex_rest.op2=registerFile.get_register(rs2);
    de_ex_rest.branch_target=imm;

    if(mycontrol_unit.isImmediate){
        de_ex_rest.B=imm;
    }
    else{
        de_ex_rest.B=registerFile.get_register(rs2);
    }
    printf("branch target :%d\n",de_ex_rest.branch_target);
    printf("A :%d\n",de_ex_rest.A);
    printf("B :%d\n",de_ex_rest.B);
    printf("op2 :%d\n",de_ex_rest.op2);
    printf("rd :%d\n",de_ex_rest.rd); 
}
// //executes the ALU operation based on ALUop
void execute(){
    long long int alu_result;
    alu_result=alu_unit(mycontrol_unit.aluSignal);
    if(mycontrol_unit.branchSelect==0){
        //not jalr type
        branchPC=de_ex_rest.branch_target+PC;
    }
    else if(mycontrol_unit.branchSelect==1){
        //if jalr then pc
        branchPC=alu_result;
    }
    if(mycontrol_unit.branchSignal=="nbr"){
        mycontrol_unit.setIsBranchTaken(false);
    }
    else if(mycontrol_unit.branchSignal=="ubr"){
        mycontrol_unit.setIsBranchTaken(true);
    }
    else{
        if(mycontrol_unit.branchSignal=="beq"){
            if(alu_result==0){
                mycontrol_unit.setIsBranchTaken(true);
            }
            else{
                mycontrol_unit.setIsBranchTaken(false); 
            }   
        }
        else if(mycontrol_unit.branchSignal=="bne"){
            if(alu_result!=0){
                mycontrol_unit.setIsBranchTaken(true);
            }
            else{
                mycontrol_unit.setIsBranchTaken(false); 
            }   
        }
        else if(mycontrol_unit.branchSignal=="blt"){
            if(alu_result<0){
                mycontrol_unit.setIsBranchTaken(true);
            }
            else{
                mycontrol_unit.setIsBranchTaken(false); 
            }   
        }
        else if(mycontrol_unit.branchSignal=="bge"){
            if(alu_result>=0){
                mycontrol_unit.setIsBranchTaken(true);
            }
            else{
                mycontrol_unit.setIsBranchTaken(false); 
            }   
        }    
    }
    ex_ma_rest.alu_result=alu_result;
    ex_ma_rest.op2=(unsigned int) de_ex_rest.op2;
    ex_ma_rest.rd=(unsigned int) de_ex_rest.rd;
}
// //perform the memory operation
// void mem() {
// }
// //writes the results back to register file
// void write_back() {
// }


// int read_word(char *mem, unsigned int address) {
//   int *data;
//   data =  (int*) (mem + address);
//   return *data;
// }

// void write_word(char *mem, unsigned int address, unsigned int data) {
//   int *data_p;
//   data_p = (int*) (mem + address);
//   *data_p = data;
// }
