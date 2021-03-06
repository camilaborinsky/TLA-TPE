%{
    #include "y.tab.h"
    #include <strings.h>
    #include "utils/types.h"
    #include "utils/symbol_table.h"
%}

integer -?[0-9]+
float   {integer}(\.{integer}+)?
comment \/\/.*
name [a-zA-Z][a-zA-Z0-9_]* 
text \"[^\"]*\"

%%

"I solemnly swear that I am up to no good"  { return START;}
"mischief managed" {return END;}

[\n]			{yylineno++;}
[\t ]           ;

{integer}       {yylval.value.int_val=atoi(yytext); return vINT;}
{float}     	{yylval.value.double_val=strtof(yytext,0); return vDOUBLE;}
{text}     	    {yylval.value.text_val=strdup(yytext); return vTEXT;}

[ \t]+          ;

{comment}       ;



"void"           {yylval.type = tVOID; return VOID;}
"int"           {yylval.type = tINT; return INT;}
"double"        {yylval.type = tDOUBLE; return DOUBLE;}
"bool"          {yylval.type = tBOOL; return BOOL;}
"rectangle"     {yylval.type = tRECTANGLE; return RECTANGLE;}
"circle"        {yylval.type = tCIRCLE; return CIRCLE;}
"dot"           {yylval.type = tDOT; return DOT;}
"text"          {yylval.type = tTEXT; return TEXT;}
"line"          {yylval.type = tLINE; return LINE;}
"figure"        {yylval.type = tFIGURE; return FIGURE;}

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
"join"          {return JOIN;}
"-->"           {return RIGHT_ARROW;}


"true"          {yylval.value.bool_val = 1; return TRUE;}
"false"         {yylval.value.bool_val = 0; return FALSE;}

"return"        {return RETURN;}


{name}          {yylval.string = strdup(yytext); return ID;}


.			    {return yytext[0];}
%%
