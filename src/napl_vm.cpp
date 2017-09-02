#include "napl.hpp"

#define VM_CODE_DEBUG

NaplVM::NaplVM(std::vector<vm_opcode>& opcode)
{
    this->opcode=opcode;

    init_function_map();
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

            //引数のない関数はfunction_mapから呼び出す
            default: (this->*function_map[opcode[code_counter].type])();
        }
    }
}

void NaplVM::init_function_map()
{
    function_map[opcode_type::ADD]=&NaplVM::add;
    function_map[opcode_type::SUB]=&NaplVM::sub;
    function_map[opcode_type::MUL]=&NaplVM::mul;
    function_map[opcode_type::DIV]=&NaplVM::div;
    function_map[opcode_type::MOD]=&NaplVM::mod;
    function_map[opcode_type::OUTPUT]=&NaplVM::print;
    function_map[opcode_type::JUMP]=&NaplVM::jump;
    function_map[opcode_type::JUMP_NOT]=&NaplVM::jump_not;
    function_map[opcode_type::EQ]=&NaplVM::eq;
    function_map[opcode_type::NOTEQ]=&NaplVM::noteq;
    function_map[opcode_type::GREAT]=&NaplVM::great;
    function_map[opcode_type::GREATEQ]=&NaplVM::greateq;
    function_map[opcode_type::LESS]=&NaplVM::less;
    function_map[opcode_type::LESSEQ]=&NaplVM::lesseq;
    function_map[opcode_type::EXIT]=&NaplVM::exit_vm;
    function_map[opcode_type::WRITE_MEM]=&NaplVM::write_memory;
    function_map[opcode_type::REF_MEM]=&NaplVM::ref_memory;
}

inline bool NaplVM::check_stack_type(stack_type type_1,stack_type type_2)
{
    return type_1==type_2;
}

inline void NaplVM::exit_vm()
{
    exit(1);
}

inline void NaplVM::write_memory()
{
    int addr=pop().i_value;

    switch(stack.top().type)
    {
        case stack_type::INT: memory[addr].i_value=pop().i_value; memory[addr].type=stack_type::INT; break;
        case stack_type::FLOAT: memory[addr].f_value=pop().f_value; memory[addr].type=stack_type::FLOAT; break;
        case stack_type::STRING: memory[addr].s_value=pop().s_value; memory[addr].type=stack_type::STRING; break;
        case stack_type::BOOL: memory[addr].b_value=pop().b_value; memory[addr].type=stack_type::BOOL; break;
    }
}

inline void NaplVM::ref_memory()
{
    int addr=pop().i_value;

    switch(memory[addr].type)
    {
        case stack_type::INT: push(memory[addr].i_value); break;
        case stack_type::FLOAT: push(memory[addr].f_value); break;
        case stack_type::STRING: push(memory[addr].s_value); break;
        case stack_type::BOOL: push(memory[addr].b_value); break;
    }
}

inline void NaplVM::eq()
{
    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value=pop().i_value;

            if(stack.top().type==stack_type::INT)
                push((pop().i_value==value));
            else if(stack.top().type==stack_type::FLOAT)
                push((pop().f_value==value));
            break;
        }
        case stack_type::FLOAT:
        {
            float value=pop().i_value;

            if(stack.top().type==stack_type::INT)
                stack,push((pop().i_value==value));
            else if(stack.top().type==stack_type::FLOAT)
                push((pop().f_value==value));
            break;
        }
        case stack_type::STRING: push((pop().s_value==pop().s_value)); break;
        case stack_type::BOOL: push((pop().b_value==pop().b_value)); break;
    }
}

inline void NaplVM::noteq()
{
    switch(stack.top().type)
    {
        case stack_type::INT:
        {
            int value=pop().i_value;

            if(stack.top().type==stack_type::INT)
                push((pop().i_value!=value));
            else if(stack.top().type==stack_type::FLOAT)
                push((pop().f_value!=value));
            break;
        }
        case stack_type::FLOAT:
        {
            float value=pop().i_value;

            if(stack.top().type==stack_type::INT)
                push((pop().i_value!=value));
            else if(stack.top().type==stack_type::FLOAT)
                push((pop().f_value!=value));
            break;
        }
        case stack_type::STRING: push((pop().s_value!=pop().s_value)); break;
        case stack_type::BOOL: push((pop().b_value!=pop().b_value)); break;
    }
}

inline void NaplVM::great()
{
    if(stack.top().type==stack_type::INT)
    {
        int value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value>value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value>value));
    }
    else if(stack.top().type==stack_type::FLOAT)
    {
        float value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            stack,push((pop().i_value>value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value>value));
    }
}

inline void NaplVM::greateq()
{
    if(stack.top().type==stack_type::INT)
    {
        int value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value>=value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value>=value));
    }
    else if(stack.top().type==stack_type::FLOAT)
    {
        float value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value>=value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value>=value));
    }
}

inline void NaplVM::less()
{
    if(stack.top().type==stack_type::INT)
    {
        int value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value<value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value<value));
    }
    else if(stack.top().type==stack_type::FLOAT)
    {
        float value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value<value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value<value));
    }
}

inline void NaplVM::lesseq()
{
    if(stack.top().type==stack_type::INT)
    {
        int value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value<=value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value<=value));
    }
    else if(stack.top().type==stack_type::FLOAT)
    {
        float value=pop().i_value;

        if(stack.top().type==stack_type::INT)
            push((pop().i_value<=value));
        else if(stack.top().type==stack_type::FLOAT)
            push((pop().f_value<=value));
    }
}

inline void NaplVM::jump()
{
    code_counter=opcode[code_counter].i_value;
}

inline void NaplVM::jump_not()
{
    if(!pop().b_value)
        code_counter=opcode[code_counter].i_value;
}

void NaplVM::print()
{
    switch(stack.top().type)
    {
        case stack_type::INT: std::cout<<pop().i_value<<std::endl; break;
        case stack_type::FLOAT: std::cout<<pop().f_value<<std::endl; break;
        case stack_type::STRING: std::cout<<pop().s_value<<std::flush; break;
        case stack_type::BOOL: std::cout<<(pop().b_value ? "true" : "false")<<std::endl; break;
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

inline void NaplVM::push(int value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::INT;
    stack_push.i_value=value;

    stack.push(stack_push);
}

inline void NaplVM::push(double value)
{
    vm_stack stack_push;

    stack_push.type=stack_type::FLOAT;
    stack_push.f_value=value;

    stack.push(stack_push);
}

inline void NaplVM::push(std::string value)
{
    vm_stack stack_push;
    stack_push.type=stack_type::STRING;
    stack_push.s_value=value;

    stack.push(stack_push);
}

inline void NaplVM::push(bool value)
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

        case opcode_type::JUMP: std::cout<<"[JUMP] : "<<opcode[code_counter].i_value<<std::endl; break;
        case opcode_type::JUMP_NOT: std::cout<<"[JUMP_NOT] : "<<opcode[code_counter].i_value<<std::endl; break;
        
        case opcode_type::EQ: std::cout<<"[EQ]"<<std::endl; break;
        case opcode_type::NOTEQ: std::cout<<"[NOTEQ]"<<std::endl; break;
        case opcode_type::LESS: std::cout<<"[LESS]"<<std::endl; break;
        case opcode_type::LESSEQ: std::cout<<"[LESSEQ]"<<std::endl; break;
        case opcode_type::GREAT: std::cout<<"[GREAT]"<<std::endl; break;
        case opcode_type::GREATEQ: std::cout<<"[GREATEQ]"<<std::endl; break;

        case opcode_type::WRITE_MEM: std::cout<<"[WRITE_MEM]"<<std::endl; break;
        case opcode_type::REF_MEM: std::cout<<"[REF_MEM]"<<std::endl; break;
    }
}

void NaplVM::error(std::string msg)
{
    std::cerr<<msg<<std::endl;
    exit(1);
}