/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */
/* This is my hand-made interpreter for the Reedoo Programming Language,
   I chose not to use something like lex and yacc because I didn't want to
   have to learn a new tool and be limited by what that tool can do, for
   example yacc isn't good at producing informative errors. */

/* Function Declarations */
/* The helper functions for the evaluator. Only the function, rdo_eval is used in the main reedoo.cc file */
bool rdo_ws(char c);
bool rdo_is_num(std::string is_num);

char rdo_expr_item_type(char c);

void rdo_count_opp(bool to_count_or_not);

std::string rdo_opp_to_string(char opp);
std::string rdo_eval(std::string expr);