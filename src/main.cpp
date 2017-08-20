#include "napl.hpp"
#include "napl_vm.hpp"
#include "napl_gencode.hpp"

//extern int yyparse();

GenerateCode genc;

int main(int argc,char **argv)
{
    std::cout<<"napl programming language"<<std::endl;

    genc.gencode(opcode_type::PUSH_I,10);
    genc.gencode(opcode_type::PUSH_I,10);
    genc.gencode(opcode_type::ADD);
    genc.gencode(opcode_type::OUTPUT);

    NaplVM vm(genc.get_code());

    vm.exec_code();

    return 0;
}