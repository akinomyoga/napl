%{
    #include "napl.hpp"
    #include "napl_vm.hpp"
    #include "napl_gencode.hpp"

    extern GenerateCode genc;

    extern int yylex();

    void yyerror(std::string msg)
    {
        std::cerr<<"[error]:"<<msg<<std::endl;
    }
%}

%union
{
    int Int;

    double Dbl;
    
    char *Str;
}

%token <Int> Num
%token Add Sub Mul Div Mod

%left Add Sub
%left Mul Div Mod

%%

    start_expr : expr {genc.gencode(opcode_type::OUTPUT);}

    expr : Num {genc.gencode(opcode_type::PUSH_I,$<Int>1);}
         | expr Add expr {genc.gencode(opcode_type::ADD);}
         | expr Sub expr {genc.gencode(opcode_type::SUB);}
         | expr Mul expr {genc.gencode(opcode_type::MUL);}
         | expr Div expr {genc.gencode(opcode_type::DIV);}
         | expr Mod expr {genc.gencode(opcode_type::MOD);}
         | '(' expr ')'
         ;

%%