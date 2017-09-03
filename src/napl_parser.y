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

    int scope_count=0;

    std::map<std::string,int> global_var_map;
    
    bool check_memory[MEMORY_SIZE];

    void yyerror(std::string msg);
    
    void new_scope();

    void close_scope();

    inline node_t *assign_var(std::string,node_t *);
    inline node_t *ref_var(std::string);

    void define_var(variable_type,std::string);

    int get_addr(int);
    
    ast_type translate_com(opcode_type);
%}

%union
{
    int Int;

    double Dbl;
    
    char *Str;

    opcode_type op_type;

    node_t *node;

    variable_type type;
}

%token <Int> Num Type Com
%token <Dbl> RNum
%token <Str> Id String
%token Add Sub Mul Div Mod
%token True False
%token Print
%token If Else

%left Com
%left Add Sub
%left Mul Div Mod

%type <node> expr
%type <node> assign_variable
%type <Int> if_statement

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
          | define_variable
          | assign_variable {genc.gencode_tree($<node>1);}
          | if_statement_list
          ;

block : '{' statement_list '}'
      | statement
      ;

if_statement_list : if_statement {genc.backpatch($<Int>1,genc.get_count());}
                  | if_statement Else {
                                            genc.gencode(opcode_type::JUMP,-1);
                                            $<Int>$=genc.get_count();    
                                            genc.backpatch($<Int>1,genc.get_count());
                                      }

                    block           {
                                        genc.backpatch($<Int>3,genc.get_count());
                                    }
                  ;

if_statement : If expr  {
                            genc.gencode_tree($<node>2);
                            genc.gencode(opcode_type::JUMP_NOT,-1);
                            $<Int>$=genc.get_count();
                        }

               block    {$$=$<Int>3;}
             ;

define_variable : Type Id {define_var($<type>1,$<Str>2);}
                ;

assign_variable : Id '=' expr   
                                {
                                    if(scope_count==0)
                                        $$=assign_var($<Str>1,$<node>3);
                                }

expr : expr Add expr {$$=make_node(ast_type::add,$<node>1,$<node>3);}
     | expr Sub expr {$$=make_node(ast_type::sub,$<node>1,$<node>3);}
     | expr Mul expr {$$=make_node(ast_type::mul,$<node>1,$<node>3);}
     | expr Div expr {$$=make_node(ast_type::div,$<node>1,$<node>3);}
     | expr Mod expr {$$=make_node(ast_type::mod,$<node>1,$<node>3);}
     | expr Com expr {$$=make_node(translate_com($<op_type>2),$<node>1,$<node>3);}
     | '(' expr ')'  {$$=$<node>2;}
     | Num           {$$=make_atom(ast_type::int_value,$<Int>1);}
     | RNum          {$$=make_atom(ast_type::float_value,$<Dbl>1);}
     | String        {$$=make_atom(ast_type::string_value,std::string($<Str>1));}
     | True          {$$=make_atom(ast_type::bool_value,true);}
     | False         {$$=make_atom(ast_type::bool_value,false);}
     | Id            {$$=ref_var($<Str>1);}
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

void new_scope()
{
    scope_count++;
}

void close_scope()
{
    scope_count--;
}

void define_var(variable_type type,std::string name)
{
    int addr=get_addr(1);

    if(global_var_map.count(name)!=0)
        yyerror("変数が再定義されました");

    global_var_map[name]=addr;
    check_memory[addr]=true;
}

int get_addr(int size)
{
    int count_buffer=0,start_buffer=0;
    bool cnt_buffer=false;

    for(int i=0;i<MEMORY_SIZE;i++)
    {
        if(!check_memory[i] && cnt_buffer==false)
        {
            start_buffer=i;
            count_buffer++;
            cnt_buffer=true;
        }
        else if(!check_memory[i] && cnt_buffer==true)
            count_buffer++;
        else 
        {
            start_buffer=0;
            count_buffer=0;
            cnt_buffer=false;
        }

        if(count_buffer==size)
            return start_buffer;
    }

    yyerror("メモリに空き領域が見つかりません");

    return 0;
}

inline node_t *assign_var(std::string name,node_t *value)
{
    if(global_var_map.count(name)==0)
        yyerror("\'"+name+"\' 未定義の変数が参照されました");

    return make_node(ast_type::write_memory,value,make_atom(ast_type::int_value,global_var_map[name]));
}

inline node_t *ref_var(std::string name)
{
    if(global_var_map.count(name)==0)
        yyerror("\'"+name+"\' 未定義の変数が参照されました");

    return make_node(ast_type::ref_memory,make_atom(ast_type::int_value,global_var_map[name]),nullptr);
}