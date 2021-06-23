%{
#include <stdio.h>
#include <stdlib.h>
%}
%token TRUE, FALSE, VALUE,ID,INT,DOUBLE,BOOL,RECTANGLE,CIRCLE,DOT,TEXT,LINE,IF,WHILE,LET,ASSIGN,L,LE,G,GE,EQ,NE,OR,AND,NOT,ADD,SUB,MUL,DIV,LPARENTHESIS,RPARENTHESIS,LBRACE,RBRACE,TDOT,SEP
%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'


%%
    
S         : CODE {printf("Input accepted\n"); exit(0);}
CODE      : CTL CODE
          | LOOP CODE
          | SMP CODE
          ;
SMP      : DECL
          | E
          ;
DECL     : LET ID ':' T ;

COND      : COND OR COND
          | COND AND COND
          | NOT COND
          | E

LOOP    : WHILE LPARENTHESIS COND RPARENTHESIS LBRACE CODE RBRACE {}
CTL     : IF LPARENTHESIS COND RPARENTHESIS LBRACE CODE RBRACE
        
E         : ID ASSIGN E { $$ = $3;}
          | E ADD E {$$ = $1 + $3;}
          | E SUB E {$$ = $1 - $3;}
          | E MUL E {$$ = $1 * $3;}
          | E DIV E { if($3 == 0){
                        yyerror("divide by zero");
                      }else{$$ = $1 / $3;}}
          | E L   E {$$ = $1 < $3;}
          | E G   E 
          | E LE  E
          | E GE  E
          | E EQ  E
          | E NE  E
          | E OR  E
          | E AND E
          | ID  
          | NUM
          { $$ = $1; printf("Found %d\n", $1);   }
          ;

    
E2     : E L E
         | E G E
         | E LE E
         | E GE E
         | E EQ E
         | E NE E
         | E OR E
         | E AND E
         ;    
         
T       : INT
          | DOUBLE
          | BOOL
          | RECTANGLE
          | CIRCLE
          | DOT
          | TEXT
          | LINE
          ;
%%

int yywrap()
{
        return 1;
} 

main() {
    printf("Enter the expression:\n");
    yyparse();
} 