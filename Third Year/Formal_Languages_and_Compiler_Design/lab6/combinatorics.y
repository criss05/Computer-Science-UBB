%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern FILE *yyin;
void yyerror(const char *s);
extern int yylineno;
%}


%token INPUT OUTPUT IF THEN ELSE END DEF RETURN
%token BEGIN_KW

%token ID CONST STRING_LITERAL

%token ASSIGN
%token EQ NEQ GT LT GE LE
%token PLUS MINUS TIMES DIV MOD
%token ARRANGEMENTS COMBINATIONS PERMUTATIONS FACTORIAL
%token LPAREN RPAREN COMMA

%right FACTORIAL
%right ASSIGN
%left EQ NEQ
%left GT LT GE LE
%left PLUS MINUS
%left TIMES DIV MOD ARRANGEMENTS COMBINATIONS PERMUTATIONS

%%

program:
    statement_list
;

statement_list:
      statement statement_list
    | /* epsilon */
;

statement:
      input_stmt
    | output_stmt
    | if_stmt
    | def_stmt
    | return_stmt
    | expr_stmt
    | assign_stmt
;

assign_stmt: ID ASSIGN expression ;

input_stmt: INPUT ID ;

output_stmt: OUTPUT output_item output_item_list ;

output_item:
      expression
    | STRING_LITERAL
;

output_item_list: COMMA output_item output_item_list | /* epsilon */ ;

if_stmt: IF condition THEN statement_list else_part END ;

else_part: ELSE statement_list | /* epsilon */ ;

def_stmt: DEF ID LPAREN parameters_opt RPAREN BEGIN_KW statement_list END ;

parameters_opt: parameters | /* epsilon */ ;

parameters: ID parameters_tail ;

parameters_tail: COMMA ID parameters_tail | /* epsilon */ ;

expr_stmt: expression ;

return_stmt: RETURN expression ;

expression: term expression_rest ;

expression_rest:
      operator term expression_rest
    | /* epsilon */
;

term:
      ID
    | CONST
    | LPAREN expression RPAREN
    | function_call
    | term FACTORIAL
;

function_call: ID LPAREN arguments_opt RPAREN ;

arguments_opt: arguments | /* epsilon */ ;

arguments: expression arguments_tail ;

arguments_tail: COMMA expression arguments_tail | /* epsilon */ ;

operator:
      ARRANGEMENTS
    | COMBINATIONS
    | PERMUTATIONS
    | PLUS
    | MINUS
    | TIMES
    | DIV
    | MOD
;

condition: expression comparison_op expression ;

comparison_op:
      EQ
    | NEQ
    | GT
    | LT
    | GE
    | LE
;

%%

void yyerror(const char *s) {
    extern char *yytext;
    fprintf(stderr, "Syntax error at line %d near '%s': %s\n", yylineno, yytext, s);
}

int main(int argc, char **argv) {
    extern FILE *outFile;
    if(argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if(!file) { perror("File open error"); return 1; }
        yyin = file;
    }

    outFile = fopen("output.txt", "w");
    if(!outFile) { perror("Cannot open output.txt"); return 1; }

    int result = yyparse();
    fclose(outFile);

    if(result == 0)
        printf("Syntactically correct: YES\n");
    else
        printf("Syntactically correct: NO\n");

    return result;
}