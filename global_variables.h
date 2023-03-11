#include"builtin_funcs.h"
#include"self_defined_funcs_and_classes.h"
#include "RegisterFile.h"
#include "Control_unit.h"
extern unsigned int PC;
extern int branchPC;
extern map<unsigned int,unsigned int> mem;
extern RegisterFile registerFile;
extern Control_unit mycontrol_unit;

// static unsigned int instruction_word;
// static unsigned int operand1;
// static unsigned int operand2;
struct IF_DE_rest{
  string instruction;
} ;

struct DE_EX_rest{
    int branch_target;
    int B;
    int A;
    int op2;
    int rd;
};

struct EX_MA_rest{
    int alu_result;
    unsigned int op2;
    unsigned int rd;
};
extern struct IF_DE_rest if_de_rest;
extern struct DE_EX_rest de_ex_rest;
extern struct EX_MA_rest ex_ma_rest;