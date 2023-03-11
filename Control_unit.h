#include "builtin_funcs.h"
class Control_unit{
    public:
    string instruction;
    bool isImmediate;
    string aluSignal;
    string branchSignal;
    bool isBranchTaken;
    int branchSelect;
    bool isLd;
    bool isSt;
    bool isWb;
    int nBytes;
    string wbSignal;
    Control_unit();
    void set_instruction(string instruct);
    void build_control();
    void setIsBranchTaken(bool val);
};