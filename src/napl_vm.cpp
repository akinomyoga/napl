#include "napl.hpp"
#include "napl_vm.hpp"

#define VM_CODE_DEBUG

NaplVM::NaplVM(std::vector<vm_opcode> &opcode)
{
    this->opcode=opcode;
}

void NaplVM::exec_code()
{
    for(code_counter=0;code_counter<opcode.size();code_counter++)
    {
        #ifdef VM_CODE_DEBUG
        debug();
        #endif

        switch(opcode[code_counter].type)
        {
            //stackにpushする命令の処理
            case PUSH_I: push<int>(opcode[code_counter].i_value); break;
            case PUSH_F: push<double>(opcode[code_counter].f_value); break;
            case PUSH_C: push<char>(opcode[code_counter].c_value); break;
            case PUSH_B: push<bool>(opcode[code_counter].b_value); break;

            //演算命令の処理
            case ADD: add(); break;
            case SUB: sub(); break;
            case MUL: mul(); break;
            case DIV: div(); break;
            case MOD: mod(); break;

            default: break;
        }
    }
}

void NaplVM::add()
{

}

void NaplVM::sub()
{

}

void NaplVM::mul()
{

}

void NaplVM::div()
{

}

void NaplVM::mod()
{

}

template<typename T>

void NaplVM::push(T value)
{
    vm_stack stack_push;

    if(typeid(T)==typeid(int))
    {
        stack_push.type=INT;
        stack_push.i_value=value;
    }
    else if(typeid(T)==typeid(double))
    {
        stack_push.type=FLOAT;
        stack_push.f_value=value;
    }
    else if(typeid(T)==typeid(char))
    {
        stack_push.type=CHAR;
        stack_push.c_value=value;
    }
    else if(typeid(T)==typeid(bool))
    {
        stack_push.type=BOOL;
        stack_push.b_value=value;
    }
    else
    {
        //不正な型のpushに対するエラー処理
    }

    stack.push(stack_push);
}

void NaplVM::debug()
{
    switch(opcode[code_counter].type)
    {
        case PUSH_I: std::cout<<"[PUSH_I] : "<<opcode[code_counter].i_value<<std::endl; break;
        case PUSH_F: std::cout<<"[PUSH_F] : "<<opcode[code_counter].f_value<<std::endl; break;
        case PUSH_C: std::cout<<"[PUSH_C] : "<<opcode[code_counter].c_value<<std::endl; break;
        case PUSH_B: std::cout<<"[PUSH_B] : "<<opcode[code_counter].b_value<<std::endl; break;
        case ADD: std::cout<<"[ADD]"<<std::endl; break;
        case SUB: std::cout<<"[SUB]"<<std::endl; break;
        case MUL: std::cout<<"[MUL]"<<std::endl; break;
        case DIV: std::cout<<"[DIV]"<<std::endl; break;
        case MOD: std::cout<<"[MOD]"<<std::endl; break;
    }
}