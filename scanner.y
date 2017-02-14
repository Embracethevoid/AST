%{
#include <cstdio>
#include <iostream>
//#include "expr.h"
#include "AST.h"
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int yylineno;
extern char* yytext;
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	float fval;
	char *sval;
	char *identval;
	//struct expr_val* expval;
    	program* prog;
	basic_classes* b_classes;
	basic_class* b_class;
	class_sig* class_sign;
	extend* ex;
	statements* ss;
	methods* ms;
	class_body* cb;
	statement* stmt;
	method* mtd;
	r_expr* r_exp;
	formal_args* f_args;
	formal_args_first* f_args_f;
	formal_args_idents* f_args_is;
	formal_args_ident* f_args_i;
	elifs*          ElIfs;
	elif*        ElIf;
	actual_args* a_args;
	r_exprs* r_exps;

}

// define the constant-string tokens:
%token EXTENDS CLASS WHILE IF ELSE ELIF RETURN DEF ENDL 
%token COLON SEMICOLON LP RP LB RB DOT COMMA
%token  GETS
%token MISS ILLEGAL //PLUS MINUS TIMES DIVIDE MORE ATMOST LESS ATLEAST EQUALS AND OR NOT
//%left PLUS MINUS TIMES DIVIDE
//%left MORE ATMOST LESS ATLEAST EQUALS
%left AND OR
%left NOT
%nonassoc   ATMOST MORE ATLEAST LESS
//%nonassoc    
%left PLUS MINUS 
%left TIMES DIVIDE
%nonassoc  EQUALS
%precedence NEG
%left DOT
//%token DOT
// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT_LIT
%token <fval> FLOAT
%token <sval> STRING_LIT
%token <identval> Ident
//%type <expval> R_Expr;
%type <prog> Program;
%type <b_class> Class;
%type <b_classes> Classes;
%type <class_sign> Class_Signature;
%type <ex> Extends_Ident;
%type <ss> Statements Statement_Block;
%type <ms> Methods;
%type <cb> Class_Body;
%type <stmt> Statement;
%type <mtd> Method;
%type <r_exp> R_Expr;
%type <f_args> Formal_Args;
%type <f_args_f> Formal_Args_First;
%type <f_args_is> Formal_Args_Idents;
%type <f_args_i> Formal_Args_Ident;
%type <ElIf> Elif;
%type <ElIfs> Elifs;
%type <r_exp> L_Expr;
%type <a_args> Actual_Args;
%type <r_exps> R_Exprs; 
%%
// the first rule defined is the highest-level rule, which in our
// case is just the concept of a whole "program file":
Program:
	Classes  Statements {$$ = new program(*$1,*$2);/*root = $$*/}
	;
Classes:
	{$$ = new basic_classes();}|Classes Class {$$ = $1 ,$1->m_value.push_back(*$2);}
	;
Class:
	Class_Signature Class_Body {$$ = new basic_class(*$1,*$2);}
	;
Class_Signature:
	CLASS Ident LP Formal_Args RP Extends_Ident {$$ = new class_sig($2,*$4,*$6);}|
	CLASS Ident LP Formal_Args RP {$$ = new class_sig($2,*$4);}
	;


Formal_Args:
	{$$ = new formal_args();}|Formal_Args_First Formal_Args_Idents{$$ = new formal_args(*$1,*$2);}
	;
Formal_Args_First:
	Ident COLON Ident {$$ = new formal_args_first($1,$3);}
	;

Formal_Args_Idents:
	{$$ = new formal_args_idents();}|Formal_Args_Idents Formal_Args_Ident  {$1->m_value.push_back(*$2);$$ = $1;}
	;


Formal_Args_Ident:
	COMMA Ident COLON Ident {$$ = new formal_args_ident();}
	;

Extends_Ident:
	EXTENDS Ident {$$ = new extend($2);}
	;

Class_Body:
	LB Statements Methods RB {$$ = new class_body(*$2,*$3);}
	;




Statements:
	{$$ = new statements();}|Statements Statement {$1->m_value.push_back(*$2);$$ = $1;}
	;

Statement_Block:
	LB Statements RB {$$ = $2;}
	;
Statement:

	IF R_Expr Statement_Block Elifs ELSE Statement_Block {$$ = new ifstmt($2,$3,*$4, $6);}|
	IF R_Expr Statement_Block Elifs {$$ = new ifstmt($2,$3,*$4);}  |
	WHILE R_Expr Statement_Block{$$ = new whilestmt($2,$3);}  |
	L_Expr COLON Ident GETS R_Expr SEMICOLON  {$$ = new expstmt($1,$3,$5);}|
	L_Expr GETS R_Expr  SEMICOLON{$$ = new expstmt($1,$3);}|
	R_Expr SEMICOLON  {$$ = new expstmt($1);}|
	RETURN R_Expr SEMICOLON{$$ = new returnstmt($2);}|
	RETURN SEMICOLON{$$ = new returnstmt();}
	;
	
	
Elifs:
{$$ = new elifs();}	|Elifs Elif{$$ = $1 , $$->m_value.push_back(*$2);} 
	;


Elif:
	ELIF R_Expr Statement_Block {$$ = new elif(*$2,*$3);}
	;


Methods:
	{$$ = new methods();}|Methods Method{$$ = $1,$1->m_value.push_back(*$2);} 
	;


Method:
	
	
DEF Ident LP Formal_Args RP COLON Ident Statement_Block
{$$ = new method($2);}
|

DEF Ident LP Formal_Args RP Statement_Block

{$$ = new method($2);}
	;








L_Expr:
	Ident{$$ = new make_ident($1);}|
	R_Expr DOT Ident {$$ = new element_call($1,$3);}|
	;

R_Expr:
	STRING_LIT {$$  = new make_str($1);}|
	INT_LIT {$$ = new make_int($1);}|
	L_Expr {$$ = $1;}|
	R_Expr PLUS R_Expr {$$ = new bin_operator($1,"PLUS",$3);}|
	R_Expr MINUS R_Expr {$$ = new bin_operator($1,"MINUS",$3);}|
	R_Expr TIMES R_Expr{$$ = new bin_operator($1,"TIMES",$3);}|
	R_Expr DIVIDE R_Expr{$$ = new bin_operator($1,"DIVIDE",$3);}|
	MINUS R_Expr %prec NEG{$$ = new negative_operator($2);}|
	LP R_Expr RP {$$ = $2;}|
	R_Expr EQUALS R_Expr {$$ = new bin_operator($1,"EQUALS",$3);}|
	R_Expr ATMOST R_Expr {$$ = new bin_operator($1,"ALMOST",$3);}|
	R_Expr LESS R_Expr{$$ = new bin_operator($1,"LESS",$3);}|
	R_Expr ATLEAST R_Expr{$$ = new bin_operator($1,"ATLEAST",$3);}|
	R_Expr MORE R_Expr{$$ = new bin_operator($1,"MORE",$3);}|
	R_Expr AND R_Expr{$$ = new bin_operator($1,"AND",$3);}|
	R_Expr OR R_Expr {$$ = new bin_operator($1,"OR",$3);}|
	NOT R_Expr {$$ = new not_operator($2);}|
	R_Expr DOT Ident LP Actual_Args RP {$$ = new function_call($1,$3,*$5);}|
	Ident LP Actual_Args RP{$$  = new function_call($1,*$3);}
	;

Actual_Args:
	{$$ = new actual_args();}|R_Expr R_Exprs {$$ = new actual_args(*$1,*$2);}
	;

R_Exprs:
	{$$ = new r_exprs();}|R_Exprs COMMA R_Expr {$$ = $1,$$->m_value.push_back(*$3);}
	;
	
	




	




%%

int main(int argv, char** argc) {
	// open a file handle to a particular file:
	FILE *myfile = fopen(argc[1], "r");
	// make sure it's valid:
	if (!myfile) {
		cout << "I can't open the input file!" << endl;
		return -1;
	}
	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	cout<<"Being parsing"<<endl;
	// parse through the input until there is no more:
	
	do {
		yyparse();
	} while (!feof(yyin));
	cout<<"Finished parsing with 0 errors"<<endl;
}

void yyerror(const char *s) {
	
	cout << yylineno << ": " << s <<"(at '"<<yytext<<"')"<< endl;
	// might as well halt now:
	exit(-1);
}
