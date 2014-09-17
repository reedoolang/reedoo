/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


#include <iostream>
#include <string>
#include <vector>


#include "cond.h"
#include "variables.h"

using namespace std;

vector <string> terms;

bool eval_cond(string cond) {

	string term = "";
	bool state = 0;
	int and_or_count = 0;
	bool r = true;

	for (int i = 0; i < cond.size(); i++) {
		
		if (cond[i] == '"') {
			if (state == 0) {
				state = 1;
			} else {
				state = 0;
			}
		}

		if (cond[i] == ' ' and state == 0) {
			terms.push_back(term);
			term = "";
		}
		else {
			term += cond[i];	
		}
	}

	for (int i = 0; i < terms.size(); i++) {
		//cout << terms[i] << " ";
	}
	//cout << endl;

	for (int i = 0; i < terms.size(); i++) {

		if (terms[i] == "or") {
			and_or_count++;
			if (i-3 >= 0 and i+3 < terms.size()) {
				if (terms[i] == "or") {
					if (terms[i-3] == terms[i-1]) {
						terms.clear();
						return true;
					} else {
						r = false;
					}

					if (terms[i+1] == terms[i+3]) {
						r = true;
					} else {
						r = false;
					}
				}
				
			}
		}

		if (terms[i] == "and") {
			and_or_count++;
			if (i-3 >= 0 and i+3 < terms.size()) {

				if (terms[i-3] != terms[i-1]) {
					terms.clear();
					return false;
				} else {
					r = true;
				}

				if (terms[i+1] != terms[i+3]) {
					r= false;
				} else {
					r = true;
				}
			}
		}
	}

	if (and_or_count == 0) {
		for (int i = 0; i < terms.size(); i++) {
			if (terms[i] == terms[i+2]) {
				terms.clear();
				return true;
			} else {
				terms.clear();
				return false;
			}
		}
	}

	terms.clear();
	
	return r;
}