#ifndef NAPL_HPP
#define NAPL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <stack>
#include <map>
#include <array>
#include <functional>
#include <unordered_map>

#define MEMORY_SIZE 10000
//#define DUMP_TREE

enum class opcode_type : int
{

    PUSH_I,PUSH_F,PUSH_S,PUSH_B, //スタックにpushする命令

    ADD,SUB,MUL,DIV,MOD, //演算命令

    OUTPUT, //出力命令

    JUMP,JUMP_NOT, //JUMP関連の命令

    EQ,NOTEQ,GREAT,GREATEQ,LESS,LESSEQ,AND,OR, //比較命令

    WRITE_MEM, //メモリ書き込み命令

    REF_MEM,

    EXIT, //終了命令

};

enum class variable_type : int
{

    INT,

    FLOAT,

    STRING,

    BOOL,

};

typedef struct
{

    opcode_type type; //operation codeの種類

    int i_value;
    double f_value;
    std::string s_value;
    bool b_value; //operation codeの値

}vm_opcode;

#include "napl_vm.hpp"
#include "napl_tree.hpp"
#include "napl_gencode.hpp"

#endif