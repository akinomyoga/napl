#include "napl.hpp"

extern int yyparse();
extern FILE* yyin;

GenerateCode genc;

int main(int argc,char **argv)
{
    if(argc==1)
    {
        std::cout<<"napl"<<std::endl;

        return 0;
    }
    else if(argc==2)
    {
        if((yyin=fopen(argv[1],"r"))==nullptr)
        {
            std::cerr<<argv[1]<<": ファイルをオープンできません"<<std::endl;
            return -1;
        }
    }

    #ifdef DUMP_TREE
    std::cout<<"----------AST----------"<<std::endl;
    #endif

    yyparse();

    #ifdef DUMP_TREE
    std::cout<<"-----------------------"<<std::endl;
    #endif

    NaplVM vm(genc.get_code());

    vm.exec_code();

    return 0;
}