%{
    #include "napl.hpp"
    #include "y.tab.h"
%}

%option noyywrap

ws [ \n\t]
digit [0-9]
symbol [();:]
letter [a-zA-Z_]
id {letter}({letter}|{digit})*
other .

%%

{ws}+

{symbol} {return yytext[0];}

"+" {return Add;}
"-" {return Sub;}
"*" {return Mul;}
"/" {return Div;}
"%" {return Mod;}

">"     {
            yylval.type=opcode_type::GREAT;
            return Com;
        }

">="    {
            yylval.type=opcode_type::GREATEQ;
            return Com;
        }

"<"     {
            yylval.type=opcode_type::LESS;
            return Com;
        }

"<="    {
            yylval.type=opcode_type::LESSEQ;
            return Com;
        }

"=="    {
            yylval.type=opcode_type::EQ;
            return Com;
        }

"!="    {
            yylval.type=opcode_type::NOTEQ;
            return Com;
        }

"int"       {
                yylval.Int=static_cast<int>(variable_type::INT); 
                return Type;
            }

"double"    {
                yylval.Int=static_cast<int>(variable_type::FLOAT);
                return Type;
            }

"string"    {
                yylval.Int=static_cast<int>(variable_type::STRING);
                return Type;
            }

"bool"      {
                yylval.Int=static_cast<int>(variable_type::BOOL);
                return Type;
            }

"print"     {return Print;}

{id} {char* buf = new char[yyleng+1]; memset(buf,0,yyleng+1); strncpy(buf,yytext,yyleng+1); yylval.Str = buf; return Id;}

{digit}+ {sscanf(yytext,"%d",&yylval.Int); return Num;}

{other} {std::cerr<<"\'"<<yytext[0]<<"\' 不正な文字です"<<std::endl;}

%%