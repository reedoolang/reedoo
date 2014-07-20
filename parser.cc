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


#include "parser.h"
#include "variables.h"
#include "reedoo.h"
#include "io.h"

using namespace std;

void parse(vector<string> tokens) {
  int errcount = 0;
  int linenum = 1;
  int i = 0;
  bool cond = false;
  while (i < tokens.size()) {
    
    TOP:if (tokens[i] + " " + tokens[i+1] == "print sc") {
      cout << SYNTAX_ERROR << "'print' supplied without anything to print [line " << linenum << "]" << endl;
      errcount++;
      i+=2;
      break;
    }

    if (tokens[i] + " " + tokens[i+1].substr(0,6) + " " + tokens[i+2] == "print string sc" or
        tokens[i] + " " + tokens[i+1].substr(0,3) + " " + tokens[i+2] == "print num sc" or
        tokens[i] + " " + tokens[i+1].substr(0,4) + " " + tokens[i+2] == "print expr sc" or
        tokens[i] + " " + tokens[i+1].substr(0,8) + " " + tokens[i+2] == "print variable sc") {
      if (tokens[i+1].substr(0,8) == "variable") {
        doPRINT(goGETVAR(tokens[i+1]));
      } else {
        doPRINT(tokens[i+1]);
      }
      i+=3;
    } else if (tokens[i].substr(0,8) + " " + tokens[i+1] + " " + tokens[i+2].substr(0,3) + " " + tokens[i+3] == "variable eq num sc" or
        tokens[i].substr(0,8) + " " + tokens[i+1] + " " + tokens[i+2].substr(0,6) + " " + tokens[i+3] == "variable eq string sc" or
        tokens[i].substr(0,8) + " " + tokens[i+1] + " " + tokens[i+2].substr(0,4) + " " + tokens[i+3] == "variable eq expr sc" or
        tokens[i].substr(0,8) + " " + tokens[i+1] + " " + tokens[i+2].substr(0,8) + " " + tokens[i+3] == "variable eq variable sc") {
      doASSIGN(tokens[i],tokens[i+2]);
      i+=4;
    } else if (tokens[i] + " " + tokens[i+1].substr(0,8) + " " + tokens[i+2] + " " + tokens[i+3].substr(0,6) + " " + tokens[i+4] == "if variable eqeq string opencb") {
      if (goGETVAR(tokens[i+1]).substr(7) == tokens[i+3].substr(7)) {
      	cond = true;
        //cout << "Condition true" << endl;
        i+=5;
        //goto TOP;
      } else {
        END_BRACE:if (tokens[i] != "closecb") {
          i++;
          goto END_BRACE;
        } else {
          i+=2;
          cout << "Found Closing Curly Brace" << endl;

        }

      }
    } else if (tokens[i] == "closecb") {
      i+=2;
    }

    if (errcount > 0) {
      break;
    }
  }
}