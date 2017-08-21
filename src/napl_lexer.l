%{
    #include "napl.hpp"
    #include "y.tab.h"
%}

%option noyywrap

ws [ \n\t]
digit [0-9]
symbol [();:]
other .

%%

{ws}+

{symbol} {return yytext[0];}

"+" {return Add;}
"-" {return Sub;}
"*" {return Mul;}
"/" {return Div;}
"%" {return Mod;}

">"  {return Great;}
">=" {return GreatEq;}
"<"  {return Less;}
"<=" {return LessEq;}
"==" {return Eq;}
"!=" {return NotEq;}

{digit}+ {sscanf(yytext,"%d",&yylval.Int); return Num;}

{other} {std::cerr<<"\'"<<yytext[0]<<"\' 不正な文字です"<<std::endl;}

%%