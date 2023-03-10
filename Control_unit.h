#include "builtin_funcs.h"
class Control_unit{
    public:
    string instruction;
    bool isImmediate;
    string aluSignal;
    string branchSignal;
    bool isBranchTaken;
    bool isLd;
    bool isSt;
    bool isWb;
    Control_unit();
    void set_instruction(string instruct);
    void build_control();
    void setIsBranchTaken(bool val);
};