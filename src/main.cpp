#include "napl.hpp"
#include "napl_vm.hpp"
#include "napl_gencode.hpp"

extern int yyparse();

GenerateCode genc;

int main(int argc,char **argv)
{
    std::cout<<"napl programming language"<<std::endl;

    yyparse();

    NaplVM vm(genc.get_code());

    vm.exec_code();

    return 0;
}