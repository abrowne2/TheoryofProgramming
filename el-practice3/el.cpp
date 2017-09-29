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

bool_literal bool_literal:: fold(){
	return bool_literal(value);
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
	num_expr res = result;
	num_expr* exp = &res;
	return expr(exp);
}

expr arith_expr:: fold(){
	// fold left
	expr newLeft = lhs->fold();
	//fold right
	expr newRight = rhs->fold();
	
	//attempt to evaluate
	if (newLeft.exp->type == et_int &&
		newRight.exp->type == et_int ) {
		int left = static_cast<const int_literal*>(newLeft.exp)->value;
		int right = static_cast<const int_literal*>(newRight.exp)->value;
		return arith_eval(op, left, right);
	}
	arith_expr newExpr(op, newLeft.exp, newRight.exp);
	num_expr me = newExpr;
	num_expr* out = &me;
	return expr(out);
}

expr if_expr:: fold() {
	expr newTest = rel->fold();
	if(newTest.bExp->type == et_bool){
		bool output = static_cast<const bool_literal*>(newTest.bExp)->value;		
		if(output)
			return expr(success->fold());
		else
			return expr(fail->fold());
	}
	expr newSuccess = success->fold();
	expr newfail = fail->fold();
	if_expr newExpr(newTest.bExp, newSuccess.exp, newfail.exp);
/*73:12: error: no viable conversion from 'if_expr' to 'bool_expr' bool_expr me = newExpr; ^ ~~~~~~~ ./el.hpp:74:8: note: candidate constructor (the implicit copy constructor) not viable: no known conversion from 'if_expr' to 'const bool_expr &' for 1st argument struct bool_expr { ^ ./el.hpp:74:8: note: candidate constructor (the implicit move constructor) not viable: no known conversion from 'if_expr' to 'bool_expr &&' for 1st argument ./el.hpp:75:2: note: candidate constructor not viable: no known conversion from 'if_expr' to 'bool_expr_type' for 1st argument bool_expr(bool_expr_type t) ^ 1 error generated.*/
	bool_expr me = newExpr;
	bool_expr* out = &me;
	return expr(out);
}



