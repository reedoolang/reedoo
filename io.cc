/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */
/* This is my hand-made interpreter for the Reedoo Programming Language,
   I chose not to use something like lex and yacc because I didn't want to
   have to learn a new tool and be limited by what that tool can do, for
   example yacc isn't good at producing informative errors. */

#include <iostream>
#include <string>

#include "io.h"
#include "eval.h"

using namespace std;

void doPRINT(string toPrint) {
  if (toPrint.substr(0,6) == "string") {
    toPrint = toPrint.substr (7);
    toPrint = toPrint.substr(1,toPrint.size() - 2);
  } else if (toPrint.substr(0,3) == "num") {
    toPrint = toPrint.substr (4);
  } else if (toPrint.substr(0,4) == "expr") {
    toPrint = toPrint.substr (5);
    toPrint = rdo_eval(toPrint);
  }
  cout << toPrint << endl;
}