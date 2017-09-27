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

expr arith_expr:: fold(){
	// fold left
	num_expr* newLeft = lhs->fold();

	//fold right
	num_expr* newRight = rhs->fold();

	//attempt to evaluate
	if (newLeft->type == et_int &&
		newRight->type == et_int ) {
		switch(op){
			case op_add:
				return expr(int_literal(static_cast<const int_literal*>(newLeft)->value + static_cast<const int_literal*>(newRight)->value));
			case op_sub:
				return expr(int_literal(static_cast<const int_literal*>(newLeft)->value - static_cast<const int_literal*>(newRight)->value));
			case op_mul:
				return expr(int_literal(static_cast<const int_literal*>(newLeft)->value * static_cast<const int_literal*>(newRight)->value));
			case op_div:
				if(static_cast<const int_literal*>(newRight)->value == 0)
					return expr(err(DIV_ZERO));
				return expr(int_literal(static_cast<const int_literal*>(newLeft)->value / static_cast<const int_literal*>(newRight)->value));
			case op_rem:
				return expr(int_literal(static_cast<const int_literal*>(newLeft)->value % static_cast<const int_literal*>(newRight)->value));
		}
	}
	return expr();
}



