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
            case opcode_type::PUSH_I: push(opcode[code_counter].i_value); break;
            case opcode_type::PUSH_F: push(opcode[code_counter].f_value); break;
            case opcode_type::PUSH_C: push(opcode[code_counter].c_value); break;
            case opcode_type::PUSH_B: push(opcode[code_counter].b_value); break;

            //演算命令の処理
            case opcode_type::ADD: add(); break;
            case opcode_type::SUB: sub(); break;
            case opcode_type::MUL: mul(); break;
            case opcode_type::DIV: div(); break;
            case opcode_type::MOD: mod(); break;

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

void NaplVM::push(int value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::INT;
    stack_push.i_value=value;

    stack.push(stack_push);
}

void NaplVM::push(double value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::FLOAT;
    stack_push.f_value=value;

    stack.push(stack_push);
}

void NaplVM::push(char value)
{
    vm_stack stack_push;
    stack_push.type=stack_type::CHAR;
    stack_push.c_value=value;

    stack.push(stack_push);
}

void NaplVM::push(bool value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::BOOL;
    stack_push.b_value=value;

    stack.push(stack_push);
}

void NaplVM::debug()
{
    switch(opcode[code_counter].type)
    {
        case opcode_type::PUSH_I: std::cout<<"[PUSH_I] : "<<opcode[code_counter].i_value<<std::endl; break;
        case opcode_type::PUSH_F: std::cout<<"[PUSH_F] : "<<opcode[code_counter].f_value<<std::endl; break;
        case opcode_type::PUSH_C: std::cout<<"[PUSH_C] : "<<opcode[code_counter].c_value<<std::endl; break;
        case opcode_type::PUSH_B: std::cout<<"[PUSH_B] : "<<opcode[code_counter].b_value<<std::endl; break;
        case opcode_type::ADD: std::cout<<"[ADD]"<<std::endl; break;
        case opcode_type::SUB: std::cout<<"[SUB]"<<std::endl; break;
        case opcode_type::MUL: std::cout<<"[MUL]"<<std::endl; break;
        case opcode_type::DIV: std::cout<<"[DIV]"<<std::endl; break;
        case opcode_type::MOD: std::cout<<"[MOD]"<<std::endl; break;
    }
}