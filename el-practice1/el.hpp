#include <algorithm>
/*
	Adapted from Class Notes, Specification, and Andrew Sutton
	(time constraints permitting)
*/

//NOTE:this is like an include guard; I'm included once in src compilation (?)
//can't use same macro name in more than one file with this.
#pragma once

enum log_op {
	op_and,
	op_or,
};

enum rel_op {
	op_less,
	op_equal,
	op_greater,
};

enum arith_op {
	op_add,
	op_sub,
	op_mul,
	op_div,
	op_rem,
};

//not sure about the `type` vs `kind` convention here.
enum num_expr_type {
	et_int,
	et_arg,
	et_arith,
	et_if
};

enum bool_expr_type {
	et_bool,
	et_rel,
	et_log
};

//syntactic domains below (prog, num_expr, bool_expr...)
//declaring these here makes the prog abstraction happy
struct prog;
struct num_expr;
struct bool_expr;

struct prog {
	prog(int n, num_expr* exp)
		:num_args(n), body(exp)
	{}

	prog(int n, bool_expr* exp)
		:num_args(n), bBody(exp)
	{}

	int num_args;
	num_expr* body;
	bool_expr* bBody;

	int nHeight(num_expr* cur_exp);
	int bHeight(bool_expr* cur_exp);
};

struct num_expr {
	num_expr(num_expr_type t)
		:type(t)
	{}

	num_expr_type type;
};

struct bool_expr {
	bool_expr(bool_expr_type t)
		:type(t)
	{}

	bool_expr_type type;
};

struct int_literal :num_expr {
	int_literal(int n)
		:num_expr(et_int), value(n)
	{}

	int value;
};

struct arith_expr :num_expr {
	arith_expr(arith_op op, num_expr* left, num_expr* right) 
		:num_expr(et_arith), op(op), lhs(left), rhs(right) 
	{}

	arith_op op;
	num_expr* lhs;
	num_expr* rhs;
};

struct arg_expr : num_expr {
	arg_expr(int n)
		:num_expr(et_arg), arg(n)
	{}

	int arg;
};

struct if_expr : num_expr {
	if_expr(bool_expr *c, num_expr* succeed, num_expr* failure) 
		:num_expr(et_if), comp(c), success(succeed), fail(failure)
	{}

	bool_expr* comp;
	num_expr* success;
	num_expr* fail;
};

struct bool_literal : bool_expr {
	bool_literal(bool n)
		:bool_expr(et_bool), value(n)
	{}

	bool value;
};

struct rel_expr : bool_expr {
	rel_expr(rel_op op, num_expr* left, num_expr* right)
		:bool_expr(et_bool), op(op), lhs(left), rhs(right)
	{}

	rel_op op;
	num_expr* lhs;
	num_expr* rhs;
};

struct log_expr : bool_expr {
	//left and right aren't the best choices here...
	//it's really expression one and two, but it seems ok?
	log_expr(log_op op, bool_expr* left, bool_expr* right)
		:bool_expr(et_log), op(op), lhs(left), rhs(right)
	{}

	log_op op;
	bool_expr* lhs;
	bool_expr* rhs;
};

//pass body pointer to get height of current loaded prog?
int prog::nHeight(num_expr* cur_exp) {
	switch(cur_exp->type){
		case et_int:
			return 0;
		case et_arg:
			return 1;
		case et_arith:
			return 1 + std::max(nHeight(static_cast<const arith_expr*>(cur_exp)->lhs),nHeight(static_cast<const arith_expr*>(cur_exp)->rhs));
		case et_if:
			return 1 + std::max(bHeight(static_cast<const if_expr*>(cur_exp)->comp),nHeight(static_cast<const if_expr*>(cur_exp)->success),nHeight(static_cast<const if_expr*>(cur_exp)->fail));				
	}
}

int prog::bHeight(bool_expr* cur_exp) {
	switch(cur_exp->type){
		case et_bool:
			return 0;
		case et_rel:
			return 1 + std::max(nHeight(static_cast<const rel_expr*>(cur_exp)->lhs),nHeight(static_cast<const rel_expr*>(cur_exp)->rhs));
		case et_log:
			return 1 + std::max(bHeight(static_cast<const log_expr*>(cur_exp)->lhs),bHeight(static_cast<const log_expr*>(cur_exp)->rhs));
	}
}
