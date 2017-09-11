/*
	Adapted from Class Notes, Specification, and Andrew Sutton
	(time constraints permitting)
*/

//NOTE: this is like an include guard; I'm included once in src compilation (?)
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

