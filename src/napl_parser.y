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

    opcode_type type;
}

%token <Int> Num Type Com
%token <Dbl> RNum
%token <Str> Id String
%token Add Sub Mul Div Mod
%token True False
%token Print

%left Com
%left Add Sub
%left Mul Div Mod

/*
*********文法*********

    #変数定義
        
        Type Id -> 変数定義
        Id Id   -> 構造体などの定義

    #式
        
        式 演算子 式
        Id = 式 -> 代入
        ( 式 )
        num    -> 整数
        rnum   -> 小数
        string -> 文字列
        true || false -> 論理

    #組み込み関数

        print -> 出力
*/

%%

program : global {genc.gencode(opcode_type::EXIT);}

global : 
       | global statement_list
       | error '\n' {yyerrok;}
       ;

statement_list : statement_list '\n' statement
               | statement
               ;

statement : Print expr {genc.gencode(opcode_type::OUTPUT);}
          ;

expr : expr Add expr {genc.gencode(opcode_type::ADD);}
     | expr Sub expr {genc.gencode(opcode_type::SUB);}
     | expr Mul expr {genc.gencode(opcode_type::MUL);}
     | expr Div expr {genc.gencode(opcode_type::DIV);}
     | expr Mod expr {genc.gencode(opcode_type::MOD);}
     | expr Com expr {genc.gencode($<type>2);}
     | '(' expr ')'
     | Num           {genc.gencode(opcode_type::PUSH_I,$<Int>1);}
     | RNum          {genc.gencode(opcode_type::PUSH_F,$<Dbl>1);}
     | String        {genc.gencode(opcode_type::PUSH_S,$<Str>1);}
     | True          {genc.gencode(opcode_type::PUSH_B,true);}
     | False         {genc.gencode(opcode_type::PUSH_B,false);}
     ;

%%