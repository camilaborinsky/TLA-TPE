%{
    #include "y.tab.h"
    #include <strings.h>
    #include "utils/types.h"
    #include "utils/symbol_table.h"
%}

integer -?[0-9]+
float   {integer}(\.{integer}+)?
comment \/\/.*
name [a-zA-Z]+ 
text \"[^\"]*\"

%%
[\n\t ]			;

{integer}       {yylval.integer=atoi(yytext); return vINT;}
{float}     	{yylval.decimal=strtof(yytext,0); return vDOUBLE;}
{text}     	    {yylval.string=strdup(yytext); return vTEXT;}

[ \t]+          ;

{comment}       ;


"I solemnly swear that I am up to no good"  {return BEGIN;}
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
"function"      {return FUNCTION;}

"<="            {return LE;}
">="            {return GE;}
"=="            {return EQ;}
"!="            {return NE;}
"or"            {return OR;}
"and"           {return AND;}
"not"           {return NOT;}
"mischief managed" {return RETURN;}

"true"          {yylval.bool = 1; return vBOOL;}
"false"         {yylval.bool = 0; return vBOOL;}


{name}          {yylval.string = strdup(yytext); return ID;}


.			    {return yytext[0];}
%%
