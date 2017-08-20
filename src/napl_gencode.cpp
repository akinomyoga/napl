#include "napl.hpp"
#include "napl_vm.hpp"
#include "napl_gencode.hpp"

std::vector<vm_opcode>& GenerateCode::get_code()
{
    return this->opcode;
}

int GenerateCode::get_count()
{
    return code_count;
}

void GenerateCode::gencode(opcode_type type)
{
    vm_opcode op;

    op.type=type;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,int i_value)
{
    vm_opcode op;

    op.type=type;
    op.i_value=i_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,double f_value)
{
    vm_opcode op;

    op.type=type;
    op.f_value=f_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,std::string s_value)
{
    vm_opcode op;

    op.type=type;
    op.s_value=s_value;

    opcode.push_back(op);
}

void GenerateCode::gencode(opcode_type type,bool b_value)
{
    vm_opcode op;

    op.type=type;
    op.b_value=b_value;

    opcode.push_back(op);
}