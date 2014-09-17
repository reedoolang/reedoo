/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


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
#include "cond.h"

using namespace std;

void parse(vector<string> tokens) {
  int errcount = 0;
  int linenum = 1;
  int i = 0;
  int starti = 0;
  bool cond = false;
  int cond_result = 2;
  int opencb_count = 0;
  int i_diff = 0;
  string cond_chunk = "";
  string varname = "";
  string new_cond = "";

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
      

      if (tokens[i+2].substr(0,8) == "variable") {
        doASSIGN(tokens[i],goGETVAR(tokens[i+2]));
      } else {
        doASSIGN(tokens[i],tokens[i+2]);
      }

      i+=4;
    } else if (tokens[i].substr(0,2) + " " + tokens[i+1].substr(0,4) + " " + tokens[i+2] == "if cond opencb") {
        cond_chunk = tokens[i+1].substr(5);
        new_cond = "";
        for (int it = 0; it < cond_chunk.size(); it++) {
          if (cond_chunk[it] == ' ') {
            varname = cond_chunk.substr(0,it);

            if (varname.size() > 8 and varname[10] == '%') {
              varname = goGETVAR(varname);
            }

            //cout << varname << endl;

            new_cond += varname + " ";
            cond_chunk = cond_chunk.substr(it+1);
            it = 0;
          }
        }
        //cout << new_cond << endl;
        //cout << tokens[i+1].substr(5) << endl;
        cond_result = eval_cond(new_cond);
        //cout << "----" << cond_result << "-----" << endl;
        starti = i;
        if (eval_cond(new_cond)) {
            // Run true block
            //cout << "TOKENS: " << tokens[i+1].substr(5) << eval_cond(tokens[i+1].substr(5)) << endl;
            i+=1;
        } else {
            
            //cout << "TOKENS: " << tokens[i+1].substr(5) << eval_cond(tokens[i+1].substr(5)) << endl;
            

           //while (tokens[i] != "closecb") {
              
              while (tokens[i+1] != "else" + tokens[starti].substr(2)) {
                i++;
              }
          // } 
            
           

          i++;

        }
        i+=2;
    } else if (tokens[i] == "closecb") {
        if (tokens[i+1] == "else") {
          i+=1;
          if (cond_result == 0) {

          }
        } else {
          i+=2;
        }
    } else {
        break;
    }

    if (i >= tokens.size()-2) {
      break;
    }

    if (errcount > 0) {
      break;
    }
  }
}