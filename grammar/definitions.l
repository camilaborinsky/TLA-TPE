%{
    #include "y.tab.h"
    extern int yylval;
%}

integer -?[0-9]+
float   {integer}(\.{integer}+)?
comment ;.*
/* name [a-zA-Z]+ */


%%
[\n\t ]			;

{integer}       {yylval=atoi(yytext); return VALUE;}
{float}     	{yylval=strtod(yytext,0); return VALUE;}

[ \t]+          ;

{comment}       ;

"int"           {return INT;}
"double"        {return DOUBLE;}
"bool"          {return BOOL;}
"rectangle"     {return RECTANGLE;}
"circle"        {return CIRCLE;}
"dot"           {return DOT;}
"text"          {return TEXT;}
"line"          {return LINE;}

"if"            {return IF;}
"while"         {return WHILE;}
"let"           {return LET;}

"="             {return ASSIGN;}

"<"             {return L;}
"<="            {return LE;}
">"             {return G;}
">="            {return GE;}
"=="            {return EQ;}
"!="            {return NE;}
"or"            {return OR;}
"and"           {return AND;}
"not"           {return NOT;}

"+"             {return ADD;}
"-"             {return SUB;}
"*"             {return MUL;}
"/"             {return DIV;}
"("             {return LPARENTHESIS;}
")"             {return RPARENTHESIS;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}
"."             {return TDOT;}
","             {return SEP;}
"true"          {return TRUE;}
"false"         {return FALSE;}
.				printf("Unknown token!"); yyterminate();
%%
