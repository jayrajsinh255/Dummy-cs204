#include "builtin_funcs.h"



int main(){
    char c=0xF0;
    int a =c;
    unsigned char ch=c;
    unsigned int b=(unsigned int)ch;
    printf("%X %X\n",a,b);
}