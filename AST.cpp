#include"AST.h"

node::node()
{

}


node::~node()
{

}
program::program(basic_classes c,statements s):clses(c.value()),stmts(s.value())
{
	// for (int i = 0; i< c.value().size();++i)
	// {
	// 	std::cout<<c.value()[i].name<<std::endl;
	// }

}

program::~program()
{

}


basic_class::basic_class(class_sig s, class_body b)/*:m_sign(s),m_body(b)*/
{

}
basic_class::~basic_class()
{

}
// std::vector<basic_class> classtable()
// {
// 	return std::vector<basic_class>;
// }

class_sig::class_sig(char* s,formal_args f,extend e)/*:m_name(std::string(s)),m_f_args(f),m_parent(e.value())*/
{
	
}

class_sig::class_sig(char* s,formal_args f)/*:m_name(std::string(s)),m_f_args(f)*/
{
	//m_parent = "obj";
}
// std::string class_sig::name()
// {
// 	return m_name;
// }

// std::string class_sig::parent()
// {
// 	return m_parent;
// }


class_sig::~class_sig()
{

}



extend::extend(char* i)/*:m_value(std::string(i))*/
{

}
extend::~extend()
{

}

// std::string extend::value()
// {
// 	return m_value;
// }

ident::ident(char* s)/*:m_value(std::string(s))*/
{

}


ident::~ident()
{

}
// std::string ident::value()
// {
// 	return m_value;
// }

class_body::class_body(statements s,methods m)
{

}

class_body::~class_body()
{

}

statements::statements()
{

}
statements::~statements()
{

}

statements::statements(std::vector<statement> s):m_value(s)
{
	
}
std::vector<statement> statements::value()
{
	return m_value;
}


methods::methods()
{

}

methods::methods(std::vector<method> m)/*:m_value(m)*/
{

}
methods::~methods()
{

}

// std::vector<method> methods::value()
// {
// 	return m_value;
// }

statement::statement()
{

}

statement::~statement()
{

}
method::method(char *s)/*:name(std::string(s))*/
{

}
method::~method()
{

}

basic_classes::basic_classes()
{

}

basic_classes::~basic_classes()
{

}

std::vector<basic_class> basic_classes::value()
{
	return m_value;
}

formal_args_first::formal_args_first(char* s1,char* s2)/*:m_value1(std::string(s1)),m_value2(std::string(s2))*/
{
}
formal_args_first::~formal_args_first()
{

}

// std::string formal_args_first::value()
// {
// 	return m_value1;
// }

formal_args_ident::formal_args_ident()
{

}

formal_args_ident::~formal_args_ident()
{

}

formal_args_idents::formal_args_idents()
{

}

formal_args_idents::~formal_args_idents()
{

}
formal_args::~formal_args()
{

}

formal_args::formal_args(formal_args_first f,formal_args_idents i )
{

}
formal_args::formal_args()
{

}


// formal_args::formal_args(formal_args f)
// {
// 	m_value = f.value();
// }


r_expr::r_expr()
{

}

r_expr::~r_expr()
{

}


make_int::make_int(int i)
{
	// char* to integer
}

make_int::~make_int()
{

}

// int make_int::value()
// {
// 	return m_value;
// }


make_str::make_str(char*s)/*:m_value(std::string(s))*/
{

}


make_str::~make_str()
{

}

// std::string make_str::value()
// {
// 	return m_value;
// }

bin_operator::bin_operator(r_expr* e1,char *s,r_expr* e2)
{
	// switch(s)
	// {
	// 	case("PLUS"):
	// 	{
	// 		break;
	// 	}
	// 	case("MINUS"):
	// 	{
	// 		break;
	// 	}
	// 	case("TIMES"):
	// 	{
	// 		break;
	// 	}
	// 	case("DIVIDE"):
	// 	{
	// 		break;
	// 	}
	// 	case("ATMOST"):
	// 	{
	// 		break;
	// 	}
	// 	case("ATLEAST"):
	// 	{
	// 		break;
	// 	}
	// 	case("MORE"):
	// 	{
	// 		break;
	// 	}
	// 	case("LESS"):
	// 	{
	// 		break;
	// 	}
	// 	case("EQUALS"):
	// 	{
	// 		break;
	// 	}
	// 	case("GETS"):
	// 	{
	// 		break;
	// 	}
	// 	case("AND"):
	// 	{
	// 		break;
	// 	}
	// 	case("OR"):
	// 	{
	// 		break;
	// 	}
	// 	cdefault: break;
	// }
}

bin_operator::~bin_operator()
{

}

negative_operator::negative_operator(r_expr* e)
{
	// do the neg of the value
}

negative_operator::~negative_operator()
{

}

not_operator::not_operator(r_expr* e)
{
	// do the not operation
}

not_operator::~not_operator()
{

}




r_exprs::r_exprs()
{

}


r_exprs::r_exprs(std::vector<r_expr> e):m_value(e)
{

}

r_exprs::~r_exprs()
{

}


actual_args::actual_args()
{

}

actual_args::actual_args(r_expr exp,r_exprs exps)
{
	m_value = exps.m_value;
	m_value.insert(m_value.begin(),exp);
}
actual_args::~actual_args()
{

}


function_call::function_call(r_expr* e, char* s, actual_args a)
{

	
}


function_call::function_call(char* s, actual_args a)
{

}

// function_call::function_call(expr* e, char* s, actual_args a)
// {

// }
// function_call::function_call(char* s, actual_args a)
// {

// }


function_call::~function_call()
{

}


make_ident::make_ident(char* s)
{

}

make_ident::~make_ident()
{

}

element_call::element_call(r_expr* e,char* s)
{

}
element_call::~element_call()
{

}

stmt::stmt()
{

}

stmt::~stmt()
{

}


elif::elif(r_expr e, statements s)
{

}

elif::~elif()
{

}

elifs::elifs()
{

}

elifs::~elifs()
{

}

ifstmt::ifstmt(r_expr* exp,stmt* s,elifs elfs,stmt *)
{

}

ifstmt::ifstmt(r_expr* exp,stmt* s,elifs elfs)
{

}

ifstmt::~ifstmt()
{

}
whilestmt::whilestmt(r_expr* exp,stmt * s)
{

}

whilestmt::~whilestmt()
{

}

expstmt::expstmt(r_expr* l, r_expr* r)
{

}

expstmt::expstmt(r_expr* l ,char* s,r_expr* r)
{

}

expstmt::expstmt( r_expr* r)
{

}
expstmt::~expstmt()
{

}

returnstmt::returnstmt()
{

}

returnstmt::returnstmt(r_expr* e)
{

}

returnstmt::~returnstmt()
{

}