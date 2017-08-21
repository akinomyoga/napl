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
%token Less LessEq Great GreatEq Eq NotEq

%left Less LessEq Great GreatEq Eq NotEq
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
         | expr Eq expr {genc.gencode(opcode_type::EQ);}
         | expr NotEq expr {genc.gencode(opcode_type::NOTEQ);}
         | expr Great expr {genc.gencode(opcode_type::GREAT);}
         | expr GreatEq expr {genc.gencode(opcode_type::GREATEQ);}
         | expr Less expr {genc.gencode(opcode_type::LESS);}
         | expr LessEq expr {genc.gencode(opcode_type::LESSEQ);}
         ;

%%