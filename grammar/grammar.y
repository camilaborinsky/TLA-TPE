%{

#include <stdio.h>
#include <stdlib.h>
#include "utils/symbol_table.h"

int yylex();
void yyerror();

%}

%union{
  char * string;
  int integer;
  float decimal;
  int type;
}

%token<string> ID
%token<decimal> NUM
%token<type> INT DOUBLE BOOL RECTANGLE CIRCLE DOT TEXT LINE
%token TRUE FALSE VALUE IF WHILE LET LE GE EQ NE OR AND NOT
%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start S



%%
    
S         : CODE {printf("Input accepted"); exit(0);}
            ;

CODE      : CTL CODE
          | LOOP CODE
          | SMP CODE
          | E ';'
          |
          ;

SMP      : DECL
         ;

DECL     : LET ID ':' T ';'  {printf("variable %s\n",$2);}
         ;

COND      : COND OR COND
          | COND AND COND
          | NOT COND
          | E
          ;

LOOP    : WHILE '(' COND ')' '{' CODE '}'
          ;
CTL     : IF '(' COND ')' '{' CODE '}'
          ;

   
E         : 
            ID '=' E 
          | E '+' E //{$$ = $1 + $3;}
          | E '-' E //{$$ = $1 - $3;}
          | E '*' E //{$$ = $1 * $3;}
          | E '/' E 
          /* { if($3 == 0){ */
                        /* yyerror("'/'ide by zero"); */
                      /* }else{$$ = $1 / $3;}} */
          | E '<'   E //{$$ = $1 < $3;}
          | E '>'   E 
          | E LE  E
          | E GE  E
          | E EQ  E
          | E NE  E
          | E OR  E
          | E AND E
          | ID  {printf("ID=%s \n",$1);}
          | NUM {  printf("Found %f\n", $1);   }
          ;   
         
T         : 
            INT 
          | DOUBLE
          | BOOL
          | RECTANGLE
          | CIRCLE
          | DOT
          | TEXT
          | LINE
          ;
%%

int yywrap(){
        return 1;
} 

int main() {
    printf("Enter the expression:\n");
    yyparse();
} 