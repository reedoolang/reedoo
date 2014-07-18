/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */
/* This is my hand-made interpreter for the Reedoo Programming Language,
   I chose not to use something like lex and yacc because I didn't want to
   have to learn a new tool and be limited by what that tool can do, for
   example yacc isn't good at producing informative errors. */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <functional>

/* Include our eval.h header file */
#include "eval.h"

/* Global variables */
/* This vector holds our numbers as we evaluate our expression. */
std::vector<std::string> rdo_num_stack;

/* opp_count is used to work out when we have finished evaluating a bracket, so that we can remove the brackets. */
int opp_count = 0;

using namespace std;

/* Check whether the char c is a space or not */
bool rdo_ws(char c) {
	if (c != ' ')
		return 0;
	else
		return 1;
}

/* Identify each character in the expression using this function.
   n = number
   o = opperator
   b = bracket */
char rdo_expr_item_type(char c) {

	switch(c) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			c = 'n';
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			c = 'o';
			break;
		case '(':
		case ')':
			c = 'b';
			break;
	}

	return c;

}

/* Convert each character literal into a 1 character long string */
string rdo_opp_to_string(char opp) {

	string o = "";

	switch(opp) {
		case '+':
			o = "+";
			break;
		case '-':
			o = "-";
			break;
		case '/':
			o = "/";
			break;
		case '*':
			o = "*";
			break;
		case '(':
			o = "(";
			break;
		case ')':
			o = ")";
			break;
	}

	return o;

}

/* Returns true if the string provided isn't an opperator. This is because if it's not an
   opperator we assume it's a number. */
bool rdo_is_num(string is_num) {
	if (is_num == "+" or
		is_num == "-" or
		is_num == "/" or
		is_num == "*" or
		is_num == "(" or
		is_num == ")") {
		return 0;
	}
	return 1;
}

/* Count the number of opperators so that we know when to remove the brackets. */
void rdo_count_opp(bool to_count_or_not) {
	if (to_count_or_not == 1)
		opp_count++;
}

/* This function actually evaluates each expression. The above functions are helper functions
   that provide functionality to the rdo_eval function. The rdo_eval function is the function
   that gets included in the main reedoo.cc file. */
string rdo_eval(string expr) {

	string result;
	string num_holder = "";
	string temp_result = "";
	string num1 = "";
	string num2 = "";
	int n2 = 0;
	int i;
	int iter;
	int bcount = 0;
	int depth = 0;
	int current_depth = 0;
	int diff = 0;
	int diff2 = 0;
	int current_b = 0;
	int minus_count = 0;
	int minus_start = 0;
	int plus_count = 0;
	int plus_start = 0;
	bool found_end = 0;
	bool got_diff = 0;
	bool to_inverse = 0;
	bool do_calc = 0;

	for (i = 0; i < expr.length();i++) {

		if (!rdo_ws(expr[i])) {
			if (rdo_expr_item_type(expr[i]) == 'n' or rdo_expr_item_type(expr[i]) == 'o' or rdo_expr_item_type(expr[i]) == 'b') {

				if (rdo_expr_item_type(expr[i]) == 'n') {

					num_holder += expr[i];

				} else if (rdo_expr_item_type(expr[i]) == 'o') {

					if (num_holder != "") {

						rdo_num_stack.push_back(num_holder);
						num_holder = "";

					}

					rdo_num_stack.push_back(rdo_opp_to_string(expr[i]));

				} else {

					if (num_holder != "") {

						rdo_num_stack.push_back(num_holder);
						num_holder = "";

					}

					rdo_num_stack.push_back(rdo_opp_to_string(expr[i]));
					bcount++;

				}
			
			} else {
				//cout << expr[i] << endl;
				cout << "Invalid character in expression" << endl;
				exit(0);
			}

			if (i == expr.length()-1 and num_holder != "") {

				rdo_num_stack.push_back(num_holder);
				num_holder = "";

			}

		}

	}

	if (bcount % 2 != 0) {
		cout << "Extra / Missing parens." << endl;
		exit(0);
	} else {
		bcount /= 2;
	}

	for (i = 0; i < rdo_num_stack.size();i++) {
		if (rdo_num_stack[i] == "(") {
			current_b++;
			
		}
		if (current_b == bcount and !found_end) {
			if (i == 1)
				depth = 0;
			else
				depth = i;
			found_end = 1;
		}
		if (rdo_num_stack[i] == ")" and found_end and !got_diff) {
			diff = i - depth;
			got_diff = 1;
		}
	}


	for (i = depth; i < depth+diff; i++) {

		if (rdo_num_stack[i] == "+" or rdo_num_stack[i] == "-" or rdo_num_stack[i] == "*" or rdo_num_stack[i] == "/") {
			if (rdo_num_stack[i-1] == "(" and rdo_num_stack[i] == "-") {
				rdo_count_opp(0);
			} else if (rdo_num_stack[i-1] == "(" and rdo_num_stack[i] == "+") {
				rdo_count_opp(0);
			} else {
				rdo_count_opp(1);
			}
		}
	
	}


	for (i = depth; i <= depth+diff;i++) {

		if (rdo_num_stack[i] == "+" and rdo_num_stack[i+1] == "-") {

			rdo_num_stack.erase(rdo_num_stack.begin()+i);
			diff -= 1;
		}
		if (rdo_num_stack[i] == "-" and rdo_num_stack[i+1] == "+") {

			rdo_num_stack.erase(rdo_num_stack.begin()+i+1);
			diff -= 1;
		}
	}
		
	for (i = depth; i <= depth+diff;i++) {
		if (rdo_num_stack[i] == "-") {

			minus_count++;

			if (minus_start == 0) {
				minus_start = i;
			}
			
		}
		if (rdo_num_stack[i] != "-") {

			if (minus_count != 0 and minus_count % 2 == 0) {
				
				for (iter = minus_start;iter < minus_start+minus_count;iter++) {
					rdo_num_stack[iter] = "";
				}
				if (rdo_num_stack[minus_start+minus_count] != "" and rdo_num_stack[minus_start+minus_count][0] != '+') {
				rdo_num_stack[minus_start+minus_count] = "+" + rdo_num_stack[minus_start+minus_count];
				}
				minus_start = 0;
				minus_count = 0;

			} else if (minus_count != 0 and minus_count % 2 != 0) {
				
				for (iter = minus_start;iter < minus_start+minus_count;iter++) {
					rdo_num_stack[iter] = "";
				}
				rdo_num_stack[minus_start+minus_count] = "-" + rdo_num_stack[minus_start+minus_count];
				minus_start = 0;
				minus_count = 0;

			}
		}
	}

	for (i = depth; i <= depth+diff;i++) {
		if (rdo_num_stack[i] == "+") {

			plus_count++;

			if (plus_start == 0) {
				plus_start = i;
			}
			
		}
		if (rdo_num_stack[i] != "+") {
			for (iter = plus_start;iter < plus_start+plus_count;iter++) {
					rdo_num_stack[iter] = "";
				}
				if (rdo_num_stack[plus_start+plus_count] != "" and rdo_num_stack[plus_start+plus_count][0] != '(') {
				rdo_num_stack[plus_start+plus_count] = "+" + rdo_num_stack[plus_start+plus_count];
				}

				plus_start = 0;
				plus_count = 0;
		}
	}

	for (i = depth+diff;i >= depth;i--) {
		if (i - 1 >= depth) {
			if (rdo_num_stack[i-1] == "(" and rdo_num_stack[i] != "(" and rdo_num_stack[i][0] != '+' and rdo_num_stack[i][0] != '-'  and rdo_num_stack[i] != "") {
				rdo_num_stack[i] = "+" + rdo_num_stack[i];
			}
			if (rdo_num_stack[i] == "/" and rdo_num_stack[i-1][0] != '+' and rdo_num_stack[i-1][0] != '-') {
				rdo_num_stack[i-1] = "+" + rdo_num_stack[i-1];
			}
			if (rdo_num_stack[i] == "/" and rdo_num_stack[i+1][0] != '+' and rdo_num_stack[i+1][0] != '-') {
				rdo_num_stack[i+1] = "+" + rdo_num_stack[i+1];
			}
			if (rdo_num_stack[i] == "*" and rdo_num_stack[i-1][0] != '+' and rdo_num_stack[i-1][0] != '-') {
				rdo_num_stack[i-1] = "+" + rdo_num_stack[i-1];
			}
			if (rdo_num_stack[i] == "*" and rdo_num_stack[i+1][0] != '+' and rdo_num_stack[i+1][0] != '-') {
				rdo_num_stack[i+1] = "+" + rdo_num_stack[i+1];
			}
		}
		if (rdo_num_stack[i] == "") {
			rdo_num_stack.erase(rdo_num_stack.begin()+i);
			diff-=1;
		}
	}

	for (i = 0; i < rdo_num_stack.size();i++) {
		//cout << rdo_num_stack[i] << endl;
	}

	div_loop:for (i = depth+diff;i >= depth;i--) {
    		
    		if (rdo_num_stack[i] == "/") {
    			result = to_string(stof(rdo_num_stack[i-1]) / stof(rdo_num_stack[i+1]));
    			if (result[0] != '+' and result[0] != '-') {
					result = "+" + result;
				}
    			rdo_num_stack[i-1] = result;
    			rdo_num_stack.erase(rdo_num_stack.begin()+i);
    			rdo_num_stack.erase(rdo_num_stack.begin()+i);
    			//cout << result << endl;
    			diff -= 2;

    			goto div_loop;
    		}
    }

	mul_loop:for (i = depth+diff;i >= depth;i--) {
    		
    		if (rdo_num_stack[i] == "*") {
    			result = to_string(stof(rdo_num_stack[i-1]) * stof(rdo_num_stack[i+1]));
    			if (result[0] != '+' and result[0] != '-') {
					result = "+" + result;
				}
    			rdo_num_stack[i-1] = result;
    			rdo_num_stack.erase(rdo_num_stack.begin()+i);
    			rdo_num_stack.erase(rdo_num_stack.begin()+i);
    			//cout << result << endl;
    			diff -= 2;

    			goto mul_loop;
    		}

    		
    }
  

	minus_loop:for (i = depth; i <= depth+diff;i++) {
		
		if (rdo_num_stack[i][0] == '-' and rdo_num_stack[i-1] != "(") {
			
			result = to_string(stof(rdo_num_stack[i]) + stof(rdo_num_stack[i-1]));
			if (result[0] != '+' and result[0] != '-') {
				result = "+" + result;
			}
			rdo_num_stack[i-1] = result;
			rdo_num_stack.erase(rdo_num_stack.begin()+i);
			diff-=1;
			
			goto minus_loop;

		}

	} 

	plus_loop:for (i = depth; i <= depth+diff;i++) {
		
		if (rdo_num_stack[i][0] == '+' and rdo_num_stack[i-1] != "(") {
			
			result = to_string(stof(rdo_num_stack[i]) + stof(rdo_num_stack[i-1]));
			if (result[0] != '+' and result[0] != '-') {
				result = "+" + result;
			}
			rdo_num_stack[i-1] = result;

			rdo_num_stack.erase(rdo_num_stack.begin()+i);
			diff-=2;
			goto plus_loop;

		}

	}
 
	opp_count = 0;

	for (i = 0; i < rdo_num_stack.size();i++) {
		
		if (rdo_num_stack[i] == "+" or rdo_num_stack[i] == "-" or rdo_num_stack[i] == "*" or rdo_num_stack[i] == "/") {

			opp_count++;

		}

	}

	if (opp_count > 0) {

		for (i = depth; i < depth+diff;i++) {
			if (rdo_num_stack[i] == "(" and rdo_num_stack[i+2] == ")") {
				rdo_num_stack.erase(rdo_num_stack.begin()+i);
				rdo_num_stack.erase(rdo_num_stack.begin()+i+1);

			}
		}

	}

	expr = "";

	for (i = 0; i < rdo_num_stack.size();i++) {
		expr += rdo_num_stack[i];
	}

	expr = "";
	bcount = 0;
	depth = 0;
	for (i = 0; i < rdo_num_stack.size();i++) {
		expr += rdo_num_stack[i];
		if (rdo_num_stack[i] == "(") {
			bcount++;
			depth = i;
		}
	}
    
    result = rdo_num_stack[depth+1];

	rdo_num_stack.clear();
	if (opp_count > 0)
		return rdo_eval(expr);
	else
		expr = to_string(stoi(result));
		return expr;
}