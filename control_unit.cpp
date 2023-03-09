#include<iostream>
#include<string>
//ingnored auipc
using namespace std;
class Control_unit{
    string instruction;
    bool isImmediate=false;
    string aluSignal="add";
    void set_instruction(string instruct){
        instruction=instruct;
    }
    void build_control(){
        string opcode=instruction.substr(25,7);
        if(opcode=="0010011"||opcode=="0000011"||opcode=="0100011"||opcode=="1100111"||opcode=="0110111"){
            isImmediate=true; //one for arithmetic immediate, load, store, jalr, lui,
        }
        else{
            isImmediate=false;
        }
        if(opcode=="0110011"||opcode=="0010011"){
            string funct3=instruction.substr(17,3);
            string funct7=instruction.substr(0,7);
            if(funct3=="000"){
                if(opcode=="0110011"){
                    if(funct7=="0000000"){
                        aluSignal="add";
                    }
                    else if(funct7=="0100000"){
                        aluSignal="sub";
                    }
                }
                else if(opcode=="0010011"){
                    aluSignal="add";
                }
            }
            else if(funct3=="100"){
                aluSignal="xor";
            }
            else if(funct3=="110"){
                aluSignal="or";
            }
            else if(funct3=="111"){
                aluSignal="and";
            }
            else if(funct3=="001"){
                aluSignal="sll";
            }
            else if(funct3=="101"){
                if(funct7=="0000000"){
                    aluSignal="srl";
                }
                else if(funct7=="0100000"){
                    aluSignal="sra";
                }   
            }
            else if(funct3=="010"){
                aluSignal="slt";
            }
            else if(funct3=="011"){
                aluSignal="sltu";
            }
        }
        if(opcode=="0000011"||opcode=="0100011"){
            aluSignal="add";
        }

        //for branch arithmetic operatio is subtraction
        if(opcode=="1100011"){
            aluSignal="sub";
        }

        //for jalr addition
        if(opcode=="1100111"){
            aluSignal="add";
        }


        
    }
    


};