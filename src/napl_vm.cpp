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
            case opcode_type::PUSH_S: push(opcode[code_counter].s_value); break;
            case opcode_type::PUSH_B: push(opcode[code_counter].b_value); break;

            //演算命令の処理
            case opcode_type::ADD: add(); break;
            case opcode_type::SUB: sub(); break;
            case opcode_type::MUL: mul(); break;
            case opcode_type::DIV: div(); break;
            case opcode_type::MOD: mod(); break;

            //出力
            case opcode_type::OUTPUT: print(); break;

            default: break;
        }
    }
}

inline bool NaplVM::check_stack_type(stack_type type_1,stack_type type_2)
{
    return type_1==type_2;
}

void NaplVM::print()
{
    switch(stack.top().type)
    {
        case stack_type::INT: std::cout<<pop().i_value<<std::flush; break;
        case stack_type::FLOAT: std::cout<<pop().f_value<<std::flush; break;
        case stack_type::STRING: std::cout<<pop().s_value<<std::endl; break;
        case stack_type::BOOL: std::cout<<pop().b_value<<std::flush; break;
    }
}

void NaplVM::add()
{
    vm_stack result_stack;

    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value_1=pop().i_value;

            if(check_stack_type(stack_type::INT,stack.top().type))
            {
                result_stack.type=stack_type::INT;
                result_stack.i_value=pop().i_value+value_1;
            }
            else if(check_stack_type(stack_type::FLOAT,stack.top().type))
            {
                result_stack.type=stack_type::FLOAT;
                result_stack.f_value=pop().f_value+(double)value_1;
            }

            break;
        }
        case stack_type::FLOAT:
        {
            double value_1=pop().f_value;

            result_stack.type=stack_type::FLOAT;

            if(check_stack_type(stack_type::FLOAT,stack.top().type))
                result_stack.f_value=pop().f_value+value_1;
            else if(check_stack_type(stack_type::INT,stack.top().type))
                result_stack.f_value=(double)pop().i_value+value_1;

            break;
        }
        
        default: error("不正な値に対して演算が行われました");
    }

    stack.push(result_stack);
}

void NaplVM::sub()
{
    vm_stack result_stack;

    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value_1=pop().i_value;

            if(check_stack_type(stack_type::INT,stack.top().type))
            {
                result_stack.type=stack_type::INT;
                result_stack.i_value=pop().i_value-value_1;
            }
            else if(check_stack_type(stack_type::FLOAT,stack.top().type))
            {
                result_stack.type=stack_type::FLOAT;
                result_stack.f_value=pop().f_value-(double)value_1;
            }

            break;
        }
        case stack_type::FLOAT:
        {
            double value_1=pop().f_value;

            result_stack.type=stack_type::FLOAT;

            if(check_stack_type(stack_type::FLOAT,stack.top().type))
                result_stack.f_value=pop().f_value-value_1;
            else if(check_stack_type(stack_type::INT,stack.top().type))
                result_stack.f_value=(double)pop().i_value-value_1;

            break;
        }
        
        default: error("不正な値に対して演算が行われました");
    }

    stack.push(result_stack);
}

void NaplVM::mul()
{
    vm_stack result_stack;

    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value_1=pop().i_value;

            if(check_stack_type(stack_type::INT,stack.top().type))
            {
                result_stack.type=stack_type::INT;
                result_stack.i_value=pop().i_value*value_1;
            }
            else if(check_stack_type(stack_type::FLOAT,stack.top().type))
            {
                result_stack.type=stack_type::FLOAT;
                result_stack.f_value=pop().f_value*(double)value_1;
            }

            break;
        }
        case stack_type::FLOAT:
        {
            double value_1=pop().f_value;

            result_stack.type=stack_type::FLOAT;

            if(check_stack_type(stack_type::FLOAT,stack.top().type))
                result_stack.f_value=pop().f_value*value_1;
            else if(check_stack_type(stack_type::INT,stack.top().type))
                result_stack.f_value=(double)pop().i_value*value_1;

            break;
        }
        
        default: error("不正な値に対して演算が行われました");
    }

    stack.push(result_stack);
}

void NaplVM::div()
{
    vm_stack result_stack;

    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value_1=pop().i_value;

            if(check_stack_type(stack_type::INT,stack.top().type))
            {
                result_stack.type=stack_type::INT;
                result_stack.i_value=pop().i_value/value_1;
            }
            else if(check_stack_type(stack_type::FLOAT,stack.top().type))
            {
                result_stack.type=stack_type::FLOAT;
                result_stack.f_value=pop().f_value/(double)value_1;
            }

            break;
        }
        case stack_type::FLOAT:
        {
            double value_1=pop().f_value;

            result_stack.type=stack_type::FLOAT;

            if(check_stack_type(stack_type::FLOAT,stack.top().type))
                result_stack.f_value=pop().f_value/value_1;
            else if(check_stack_type(stack_type::INT,stack.top().type))
                result_stack.f_value=(double)pop().i_value/value_1;

            break;
        }
        
        default: error("不正な値に対して演算が行われました");
    }

    stack.push(result_stack);
}

void NaplVM::mod()
{
    vm_stack result_stack;

    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value_1=pop().i_value;

            if(check_stack_type(stack_type::INT,stack.top().type))
            {
                result_stack.type=stack_type::INT;
                result_stack.i_value=pop().i_value%value_1;
            }

            break;
        }
        
        default: error("不正な値に対して演算が行われました");
    }

    stack.push(result_stack);
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

void NaplVM::push(char* value)
{
    vm_stack stack_push;
    stack_push.type=stack_type::STRING;
    stack_push.s_value=value;

    stack.push(stack_push);
}

void NaplVM::push(bool value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::BOOL;
    stack_push.b_value=value;

    stack.push(stack_push);
}

vm_stack NaplVM::pop()
{
    vm_stack s=stack.top();

    stack.pop();

    return s;
}

void NaplVM::debug()
{
    switch(opcode[code_counter].type)
    {
        case opcode_type::PUSH_I: std::cout<<"[PUSH_I] : "<<opcode[code_counter].i_value<<std::endl; break;
        case opcode_type::PUSH_F: std::cout<<"[PUSH_F] : "<<opcode[code_counter].f_value<<std::endl; break;
        case opcode_type::PUSH_S: std::cout<<"[PUSH_S] : "<<opcode[code_counter].s_value<<std::endl; break;
        case opcode_type::PUSH_B: std::cout<<"[PUSH_B] : "<<opcode[code_counter].b_value<<std::endl; break;

        case opcode_type::ADD: std::cout<<"[ADD]"<<std::endl; break;
        case opcode_type::SUB: std::cout<<"[SUB]"<<std::endl; break;
        case opcode_type::MUL: std::cout<<"[MUL]"<<std::endl; break;
        case opcode_type::DIV: std::cout<<"[DIV]"<<std::endl; break;
        case opcode_type::MOD: std::cout<<"[MOD]"<<std::endl; break;

        case opcode_type::OUTPUT: std::cout<<"[OUTPUT]"<<std::endl; break;
    }
}

void NaplVM::error(std::string msg)
{
    std::cerr<<msg<<std::endl;
    exit(1);
}