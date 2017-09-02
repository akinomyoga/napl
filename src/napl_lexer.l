%{
    #include "napl.hpp"
    #include "y.tab.h"

    extern void yyerror(std::string);

    char *scan_string();
%}

%option noyywrap

ws [ \n\t]
digit [0-9]
symbol [();:=]
letter [a-zA-Z_]
id {letter}({letter}|{digit})*
string \"([^\"\\\n]|\\.)*[\"\n]
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
            yylval.op_type=opcode_type::GREAT;
            return Com;
        }

">="    {
            yylval.op_type=opcode_type::GREATEQ;
            return Com;
        }

"<"     {
            yylval.op_type=opcode_type::LESS;
            return Com;
        }

"<="    {
            yylval.op_type=opcode_type::LESSEQ;
            return Com;
        }

"=="    {
            yylval.op_type=opcode_type::EQ;
            return Com;
        }

"!="    {
            yylval.op_type=opcode_type::NOTEQ;
            return Com;
        }

"int"       {
                yylval.type=variable_type::INT; 
                return Type;
            }

"double"    {
                yylval.type=variable_type::FLOAT;
                return Type;
            }

"string"    {
                yylval.type=variable_type::STRING;
                return Type;
            }

"bool"      {
                yylval.type=variable_type::BOOL;
                return Type;
            }

"true"      {return True;}

"false"     {return False;}

"print"     {return Print;}

{id} {char* buf = new char[yyleng+1]; memset(buf,0,yyleng+1); strncpy(buf,yytext,yyleng+1); yylval.Str = buf; return Id;}

{digit}+ {sscanf(yytext,"%d",&yylval.Int); return Num;}

{digit}+"."{digit}* {sscanf(yytext,"%lf",&yylval.Dbl); return RNum;}

{string} {yylval.Str=scan_string(); return String;}

{other} {std::cerr<<"\'"<<yytext[0]<<"\' 不正な文字です"<<std::endl;}

%%

char *scan_string()
{
    char *p,*q;

    if(yytext[yyleng-1]!='\"')yyerror("Unterminated string literal");

    for(p=yytext+1,q=yytext;p<yytext+(yyleng-1);*(q++)=*(p++))
    {
        if(*p=='\\')
        {
            if(*(++p)=='n')*p='\n';
            else if(*p=='t')*p='\t';
        }
    }
    
    *q='\0';

    yyleng=q-yytext;

    return yytext;
}