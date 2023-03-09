#include "builtin_funcs.h"
int sign_extn(string bin){
    string temp;
    int imm=0;
    int itr=32-bin.length();
    if(bin[0]=='1'){
        temp="";
        for(int i=0;i<itr;i++){
            temp.push_back('1');
        }
        bin=temp+bin;
        imm=bin2dec(bin);
    }
    else{
        temp="";
        for(int i=0;i<itr;i++){
            temp.push_back('0');
        }
        bin=temp+bin;
        imm=bin2dec(bin);
    } 
    return imm;

}
int unsign_extn(string bin){
    string temp;
    int imm=0;
    int itr=32-bin.length();
    temp="";
    for(int i=0;i<itr;i++){
        temp.push_back('0');
    }
    bin=temp+bin;
    imm=bin2dec(bin);
    return imm;
}
int immediate(string instruction){
    string opcode=instruction.substr(25,7);
    int imm=0;
    string imm_str;
    string temp;
    if(opcode=="0010011"||opcode=="0000011"||opcode=="1100111"){
        //arithmetic-immediate, load and jalr
        string funct3=instruction.substr(17,3);
        if((opcode=="0010011")&&(funct3=="001"||funct3=="101")){
            imm_str=instruction.substr(7,5);
            imm=sign_extn(imm_str);
        }
        else{
            imm_str=instruction.substr(0,12);
            imm=sign_extn(imm_str);
        }   
    }
    else if(opcode=="0100011"){
        imm_str=instruction.substr(0,7)+instruction.substr(20,5);
        imm=sign_extn(imm_str);
    }
    else if(opcode=="1100011"){
        imm_str=instruction.substr(0,1)+instruction.substr(24,1)+instruction.substr(1,6)+instruction.substr(20,4)+"0";
        imm=sign_extn(imm_str);
    }
    else if(opcode=="1101111"){
        imm_str=instruction.substr(0,1)+instruction.substr(12,8)+instruction.substr(11,1)+instruction.substr(30,10);
        imm=sign_extn(imm_str);
    }
    else if(opcode=="1101111"||opcode=="1100111"){
        imm_str=instruction.substr(0,20);
        imm=sign_extn(imm_str);
    }
    return imm;
}
int bin2dec(string str){

}