#ifndef AST_H
#define AST_H
#include<map>
#include<string>
#include<vector>
#include<iostream>




// typedef struct expr_val* exp;
// struct expr_val
// {
// 	char* str;
// 	int num;
//     float num;
// };

// extern exp mk_int(int item);
// extern exp mk_str(char* item);
// extern exp mk_float(float item);
class node
{
public:
	node();
	~node();
	//std::string type;
protected:
	//std::string type;
	//virtual void print();
	//virtual void evalutate();
};


class expr : public node
{
public:
	expr();
	~expr();
};







class ident : public node
{
public:
	ident(char*);
	~ident();
	std::string value();
protected:
	std::string m_value;

};



class extend: public node
{
public:
	extend(char* i);
	~extend();
	std::string value();
protected:
	std::string m_value;
	//void evaluate();
};
//template <typename T>
class r_expr : public node//expr
{
public:
	r_expr();
	//r_expr(char*,int);
	// r_expr(expr* e);
	// r_expr(expr* e1, char* s, expr* e2);
	// r_expr(char*s,expr* e);
	~r_expr();
	//T value();  not sure how to do with the type of the value
private:
	//T m_value;
};


// class l_expr:public expr
// {
// public:
// 	l_expr(char*);
// 	l_expr(expr* , char*);
// 	~l_expr();
// }

class r_exprs: public node
{
public:
	r_exprs();
	r_exprs(std::vector<r_expr> e);
	~r_exprs();
	std::vector<r_expr> m_value;; 
};

class actual_args:public node
{
public:
	actual_args(r_expr exp , r_exprs e);
	actual_args();
	~actual_args();
	std::vector<r_expr> m_value;
};

class make_ident : public r_expr
{
public:
	make_ident(char*);
	~make_ident();
};


class element_call : public r_expr
{
public:
	element_call(r_expr* ,char*);
	~element_call();
};

class function_call : public r_expr
{
public:
	function_call(r_expr* e, char* s, actual_args a);
	function_call(char* s, actual_args a);
	~function_call();
};


class make_int : public r_expr
{
public:
	make_int(int i);
	~make_int();
	//int value();
private:
	//int m_value;

};

class make_str:public r_expr
{public:
	make_str(char* s);
	~make_str();
//	std::string value();
private:
//	std::string m_value;

};



class bin_operator : public r_expr
{public:
	bin_operator(r_expr* e1, char*s ,r_expr* e2);
	~bin_operator();

};

class negative_operator : public r_expr
{
public:
	negative_operator( r_expr* e);
	~negative_operator();
};

class not_operator: public r_expr
{
public:
	not_operator( r_expr *e);
	~not_operator();
};







class formal_args_first : public node
{
public:
	formal_args_first(char* s1,char* s2);
	~formal_args_first();
	//std::string value();
private:
	//std::string m_value1;
	//std::string m_value2;
};

class formal_args_ident : public node
{
public:
	formal_args_ident();
	~formal_args_ident();
	//std::vector<std::string> m_value;
	//std::vector<std::string> value();
};

class formal_args_idents : public node
{
public:
	formal_args_idents();
	~formal_args_idents();
	std::vector<formal_args_ident> m_value;
	//std::vector<formal_args_ident> value();
};





class formal_args : public node
{
public:
	formal_args();
	//formal_args(formal_args f);
	formal_args(formal_args_first f,formal_args_idents i );
	~formal_args();
	//std::vector<std::string> m_value;
	//std::vector<std::string> value();
};
class stmt:public node
{
public:
	stmt();
	~stmt();
};

class statement : public stmt
{
public:
	statement();
	~statement();
};

class method:public node
{
public:
	method(char* s);
	~method();
	//std::string type;
	//std::string name;
	//std::vector<parameters> pare;
};
class methods : public node
{
public:
	methods();
	methods(std::vector<method> m);
	~methods();
	std::vector<method> value();
	std::vector<method> m_value;

};




class statements : public stmt
{
public:
	statements();
	statements(std::vector<statement> s);
	~statements();
	std::vector<statement> value();
	std::vector<statement> m_value;

};

class elif:public node
{
public:
	elif(r_expr e, statements s);
	~elif();
};

class elifs:public node
{
public:
	elifs();
	~elifs();
	std::vector<elif> m_value;
};

class class_body:public node
{
public:
	class_body(statements s,methods m);
	~class_body();
};

class ifstmt:public statement
{
public:
	ifstmt(r_expr* exp,stmt* s,elifs elfs,stmt *);
	ifstmt(r_expr* exp,stmt* s,elifs elfs);
	~ifstmt();

};

class whilestmt : public statement
{
public:
	whilestmt(r_expr* exp,stmt * s);
	~whilestmt();
};

class expstmt: public statement
{
public:
	expstmt( r_expr* r);
	expstmt(r_expr* l ,r_expr* r);
	expstmt(r_expr* l ,char* s,r_expr* r);
	~expstmt();
};

class returnstmt : public statement
{
public:
	returnstmt();
	returnstmt(r_expr* e);
	~returnstmt();
};


class class_sig : public node
{
public:
	class_sig(char* s,formal_args f );
	class_sig(char* s, formal_args f,extend e);
	~class_sig();
	//formal_args m_f_args;
	//std::string name();
	//std::string parent();

protected:
	//std::string m_name;
	//std::string m_parent;
};



class basic_class:public node
{
public:
	basic_class(class_sig s, class_body b);
	~basic_class();
//protected:
	//class_sig m_sign;
	//class_body m_body;

	//std::string name;
	///std::string parent;
	//std::vector<std::string> method_names; 

};

class basic_classes : public node
{
public:
	basic_classes();
	~basic_classes();

	std::vector<basic_class> value();
		std::vector<basic_class> m_value;
};


//std::vector<basic_class> classtable();


class program : public node
{public:
	program(basic_classes c,statements s);
	~program();
	//std::map<std::string,std::string> classes;
protected:
private:
	std::vector<basic_class> clses;
	std::vector<statement> stmts;
};

#endif