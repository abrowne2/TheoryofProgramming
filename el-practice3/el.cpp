/*
	Author: Adam Browne
	Group work with Samuel Borick and Owen Quick
*/

// #include <cc/diagnostics.hpp>
// #include <cc/input.hpp>
// #include <cc/output.hpp>

#include "el.hpp"
#include <iostream>
#include <fstream>
#include <iterator>

int_literal int_literal:: fold(){
	return int_literal(value);
}

expr arith_expr:: arith_eval(const arith_op op, int l, int r){
	int_literal result;
	if(op == op_add){
		result = int_literal(l + r);
	} else if(op == op_sub){
		result = int_literal(l - r);
	} else if(op == op_mul){
		result = int_literal(l * r);
	} else if(op == op_div){
		if(r == 0)
			return expr(err(DIV_ZERO));
		result = int_literal(l / r);
	} else if(op == op_rem){
		result = int_literal(l % r);
	}	
	//NOTE: this may lose int_Literal value info.???
	num_expr res = result;
	num_expr* exp = &res;
	return expr(exp);
}

expr arith_expr:: fold(){
	// fold left
	num_expr* newLeft = lhs->fold();
	//fold right
	num_expr* newRight = rhs->fold();
	
	//attempt to evaluate
	if (newLeft->type == et_int &&
		newRight->type == et_int ) {
		int left = static_cast<const int_literal*>(newLeft)->value;
		int right = static_cast<const int_literal*>(newRight)->value;
		return arith_eval(op, left, right);
	}
	num_expr me = *this;
	num_expr* out = &me;
	return expr(out);
}



