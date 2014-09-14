/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

#include "reedoo.h"
#include "variables.h"
#include "eval.h"
#include "io.h"

using namespace std;

std::map<string, string> variables;

string goGETVAR(string varname) {

  if (doVARLOOKUP(varname) == 0) {

    

    return variables[varname];

  } else {

    cout << IO_ERROR << "Variable not yet declared." << endl;
    exit(1);

  }

}

void doASSIGN(string varname, string varval) {

  int vnl = 0;
  //cout << rdo_eval(varval.substr(5)) << endl;
  //varname = varname.substr(9);
  vnl = varname.length();
  if (varval.substr(0,4) == "expr") {
    varval = rdo_eval(varval.substr(5));
  }
  variables[varname] = varval;
}

int doVARLOOKUP(string var) {

  if (variables[var] == "null") {
    return 2;
  } else if (variables[var] == "") {
    return 1;
  } else {
    return 0;
  }

}
