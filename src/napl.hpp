#ifndef NAPL_HPP
#define NAPL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <stack>
#include <functional>

enum class opcode_type : int
{

    PUSH_I,PUSH_F,PUSH_S,PUSH_B, //スタックにpushする命令

    ADD,SUB,MUL,DIV,MOD, //演算命令

    OUTPUT, //出力命令

};

typedef struct
{

    opcode_type type; //operation codeの種類

    int i_value;
    double f_value;
    char* s_value;
    bool b_value; //operation codeの値

}vm_opcode;

#endif