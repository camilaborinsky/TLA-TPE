%{
    #include "y.tab.h"
    #include <strings.h>
    #include "utils/symbol_table.h"
%}

integer -?[0-9]+
float   {integer}(\.{integer}+)?
comment \/\/.*
name [a-zA-Z]+ 


%%
[\n\t ]			;

{integer}       {yylval.integer=atoi(yytext); return VALUE;}
{float}     	{yylval.decimal=strtof(yytext,0); return VALUE;}

[ \t]+          ;

{comment}       ;


"int"           {yylval.type = tINT; return INT;}
"double"        {yylval.type = tDOUBLE; return DOUBLE;}
"bool"          {yylval.type = tBOOL; return BOOL;}
"rectangle"     {yylval.type = tRECTANGLE; return RECTANGLE;}
"circle"        {yylval.type = tCIRCLE; return CIRCLE;}
"dot"           {yylval.type = tDOT; return DOT;}
"text"          {yylval.type = tTEXT; return TEXT;}
"line"          {yylval.type = tLINE; return LINE;}

"if"            {return IF;}
"while"         {return WHILE;}
"let"           {return LET;}


"<="            {return LE;}
">="            {return GE;}
"=="            {return EQ;}
"!="            {return NE;}
"or"            {return OR;}
"and"           {return AND;}
"not"           {return NOT;}

"true"          {return TRUE;}
"false"         {return FALSE;}


{name}          {yylval.string = strdup(yytext); return ID;}


.			    {return yytext[0];}
%%
