#include "builtin_funcs.h"



int main(){
    int n=0xF0000000;
    unsigned int u;
    printf("%d\n",n);
    
    u=(n)>>2;
    printf("%x\n",n);
    printf("%x\n",u);
}