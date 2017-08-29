%{
    #include "napl.hpp"

    extern int yylex();

    extern node_t *make_node(ast_type,node_t*,node_t*);
    extern node_t *make_atom(ast_type,int);
    extern node_t *make_atom(ast_type,double);
    extern node_t *make_atom(ast_type,std::string);
    extern node_t *make_atom(ast_type,bool);

    extern GenerateCode genc;
    extern int yylineno;

    void yyerror(std::string msg);
    ast_type translate_com(opcode_type);
%}

%union
{
    int Int;

    double Dbl;
    
    char *Str;

    opcode_type type;

    node_t *node;
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

%type <node> expr


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

statement : Print expr {genc.gencode_tree(make_node(ast_type::output,$<node>2,nullptr));}
          ;

expr : expr Add expr {$$=make_node(ast_type::add,$<node>1,$<node>3);}
     | expr Sub expr {$$=make_node(ast_type::sub,$<node>1,$<node>3);}
     | expr Mul expr {$$=make_node(ast_type::mul,$<node>1,$<node>3);}
     | expr Div expr {$$=make_node(ast_type::div,$<node>1,$<node>3);}
     | expr Mod expr {$$=make_node(ast_type::mod,$<node>1,$<node>3);}
     | expr Com expr {$$=make_node(translate_com($<type>2),$<node>1,$<node>3);}
     | '(' expr ')'  {$$=$<node>2;}
     | Num           {$$=make_atom(ast_type::int_value,$<Int>1);}
     | RNum          {$$=make_atom(ast_type::float_value,$<Dbl>1);}
     | String        {$$=make_atom(ast_type::string_value,$<Str>1);}
     | True          {$$=make_atom(ast_type::bool_value,true);}
     | False         {$$=make_atom(ast_type::bool_value,false);}
     ;

%%

void yyerror(std::string msg)
{
    std::cerr<<"[error]["<<yylineno<<"]:"<<msg<<std::endl;
}

ast_type translate_com(opcode_type op)
{
    switch(op)
    {
        case opcode_type::EQ: return ast_type::eq;
        case opcode_type::NOTEQ: return ast_type::noteq;
        case opcode_type::GREAT: return ast_type::great;
        case opcode_type::GREATEQ: return ast_type::greateq;
        case opcode_type::LESS: return ast_type::less;
        case opcode_type::LESSEQ: return ast_type::lesseq;
    }
}