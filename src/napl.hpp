#ifndef NAPL_HPP
#define NAPL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <stack>
#include <functional>

typedef enum
{

    PUSH_I,PUSH_F,PUSH_C,PUSH_B,//スタックにpushする命令

    ADD,SUB,MUL,DIV,MOD, //演算命令

}vm_opcode_type;

typedef struct
{

    vm_opcode_type type; //operation codeの種類

    int i_value;
    double f_value;
    char c_value;
    bool b_value; //operation codeの値

}vm_opcode;

#endif