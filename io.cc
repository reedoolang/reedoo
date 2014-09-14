/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


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