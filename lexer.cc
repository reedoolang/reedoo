/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "lexer.h"

/* Definitions */
/* These are our constants, these are defined as constant at the start of the program so
   that if anything goes wrong in the execution of the code we can always display the
   right kind of errors. */
#define IO_ERROR "[IO ERROR] "
#define SYNTAX_ERROR "[SYNTAX ERROR] "
#define ASSIGN_ERROR "[ASSIGN ERROR] "

using namespace std;

/* Global Variables */
/* Not all of these are actual "keywords" that can be used in programs.
   They are called keywords because they are reserved, either because they
   are specified as keywords in the grammar or because they are reserved by
   the interpreter for internal use. */
std::string reserved[14] = { "print", "string", "sc", "variable", "eq", "undefined", "nl", "num", "expr", "eof", "if", "else", "and", "or" };
/* We store lex_tokens in a vector, we could use an array but specifying an arrays
   size at runtime is technically impossible and the work arounds are a pain. */
std::vector<std::string> lnums;

//string s;

int lnum = 1;
int ecount = 0;

bool rdo_is_reserved(string tok) {
  int i;
  for (i = 0; i < 9;i++) {
    if (tok == reserved[i])
      return true;
    else
      return false;
  }
  return false;
}

vector<string> lex(string prog) {
  std::vector<std::string> lex_tokens;
  int i = 0;
  int ifcount = 0;
  int elsecount = 0;
  int start_ce = 0;
  int current_if = 0;
  string tok = "";
  string n = "";
  string expr = "";
  bool state = 0;
  bool expr_started = 0;
  bool is_expr = 0;
  bool var_started = 0;
  bool sl_comment_started = 0;
  bool unquoted_str_fnd = false;
  bool block_started = false;
  bool condstarted = false;
  string s = "";
  string v = "";
  string ce = "";
  string condition = "";

  for(i = 0; i < prog.size(); ++i) {
    tok += prog[i];
    //cout << tok << endl;
      if (tok == " " and state == 0) {
        tok = "";
        if (n != "") {
          //is_expr = 1;
          //lex_tokens.push_back(reserved[7] + ":" + n);
          condition += reserved[7] + ":" + expr + " ";
        }
        expr = "";
        n = "";
        if (v != "" and condstarted == false) {
          lex_tokens.push_back(reserved[3] + ":\"" + v + "\"");
          v = "";
        }
        
        var_started = 0;
      } else if (tok == ";" and state == 0) {
        tok = "";
        if (expr.length() >= expr.length()-1) {
          if (expr.substr(expr.length()-1) == "+" or expr.substr(expr.length()-1) == "-" or expr.substr(expr.length()-1) == "/" or expr.substr(expr.length()-1) == "*") {
            if (lnum == 0)
              lnum++;
            cout << SYNTAX_ERROR << "Numbers and expressions must not end with an opperator [line " << lnum << "]" << endl;
            /* If the error count goes about 0, the program immediately exits. This prevents crashes and provides a better user experience. */
            ecount++;
          }
        }
        if (expr != "" and is_expr == 1) {
          lex_tokens.push_back(reserved[8] + ":(" + expr + ")");
        } else if (n != "" and is_expr == 0) {
          condition += reserved[7] + ":" + expr;
          lex_tokens.push_back(reserved[7] + ":" + expr);
        }
        if (v != "") {
          lex_tokens.push_back(reserved[3] + ":\"" + v + "\"");
        }
        if (lex_tokens.back() != "sc") {
          lex_tokens.push_back(reserved[2]); 
        }        
        v = "";
        var_started = 0;
        n = "";
        expr = "";
        is_expr = 0;
      } 
      /* Single-line comments */
      else if (tok == "#" and state == 0) {
        /* Start of a single-line comment means end of an expression */
        if (expr != "" and is_expr == 1) {
            lex_tokens.push_back(reserved[8] + ":(" + expr + ")");
          } else if (n != "" and is_expr == 0) {
            lex_tokens.push_back(reserved[7] + ":" + expr);
          }
          /* Also means end of variables */
          if (v != "") {
            lex_tokens.push_back(reserved[3] + ":\"" + v + "\"");
          }
          /* If sl_comment_started doesn't already equal 1, set it to 1 */
        if (sl_comment_started == 0) {
          sl_comment_started = 1;
        }
        v = "";
        var_started = 0;
        n = "";
        expr = "";
        is_expr = 0;
      } else if (sl_comment_started == 1) {
        if (tok == "\n") {
          sl_comment_started = 0;
          if (lex_tokens.size() != 0) {
          if (lex_tokens.back() != "sc") {
            lex_tokens.push_back(reserved[2]); 
          } 
        }
        }
        tok = "";
      } else if (tok == "\r") {
        tok = "";
      } else if (tok == "\t") {
        tok = "";
      } else if (tok == "\n" and state == 1) {

        cout << SYNTAX_ERROR << "EOL found inside of string. [line " << lnum << "]" << endl;
        ecount++;

      } else if (tok == "\n" and state == 0) {
        
        if (state == 0) {
          tok = "";
          if (expr.length() >= expr.length()-1) {
            if (expr.substr(expr.length()-1) == "+" or expr.substr(expr.length()-1) == "-" or expr.substr(expr.length()-1) == "/" or expr.substr(expr.length()-1) == "*") {
              if (lnum == 0)
                lnum++;
              cout << SYNTAX_ERROR << "Numbers and expressions must not end with an opperator [line " << lnum << "]" << endl;
              /* If the error count goes about 0, the program immediately exits. This prevents crashes and provides a better user experience. */
              ecount++;
            }
          }
          lnum++;
          if (expr != "" and is_expr == 1) {
            lex_tokens.push_back(reserved[8] + ":(" + expr + ")");
          } else if (n != "" and is_expr == 0) {
            lex_tokens.push_back(reserved[7] + ":" + expr);
          }
          if (v != "") {
            lex_tokens.push_back(reserved[3] + ":\"" + v + "\"");
          }
          if (lex_tokens.size() != 0) {
            if (lex_tokens.back() != "sc" and lex_tokens.back() != "opencb") {
              lex_tokens.push_back(reserved[2]); 
            }   
          }    
          v = "";
          var_started = 0;
          n = "";
          expr = "";
          is_expr = 0;
        }
      } else if (tok == "%" and state == 0) {
        if (var_started == 0)
          var_started = 1;
      } else if (var_started == 1) {
        v += tok;
        tok = "";
      } else if (tok == "0" or tok == "1" or tok == "2" or tok == "3" or tok == "4" or tok == "5" 
        or tok == "6" or tok == "7" or tok == "8" or tok == "9") {
        if (state == 0) {
          n += tok;
          expr += tok;
        } else {
          s += tok;
        }
        tok = "";
      } else if (tok == "+" or tok == "-" or tok == "*" or tok == "/" or tok == "(" or tok == ")") {
        if (state == 0) {
          expr += tok;
          is_expr = 1;
          tok = "";
          n = "";
        }
      } else if (tok == "=" and state == 0) {
        if (lex_tokens.back() == "eq") {
          if (condstarted == false) {
            lex_tokens.back() = "eqeq";
          } else {
            
            if (v != "") {
              condition += "variable:\"" + v + "\" ";
              v = "";
            }
            var_started = 0;            
            condition += "eqeq ";
            lex_tokens.pop_back();

          } 
        } else {
        lex_tokens.push_back("eq");
        }
        tok = "";
      } else if (tok == reserved[12] and state == 0) {
          if (condstarted == false) {
            lex_tokens.push_back("and");
          } else {
            if (v != "") {
              condition += "variable:\"" + v + "\" ";
              v = "";
            }
            var_started = 0;     
            condition += "and ";
          } 
        tok = "";
      } else if (tok == reserved[13] and state == 0) {
          if (condstarted == false) {
            lex_tokens.push_back("or");
          } else {
            if (v != "") {
              condition += "variable:\"" + v + "\" ";
              v = "";
            }
            var_started = 0;     
            condition += "or ";
          }
        tok = "";
      } else if (tok == reserved[10]) {
        ifcount++;
        lex_tokens.push_back(reserved[10] + ":" + to_string(ifcount));
        condstarted = true;
        condition = "cond:";
        tok = "";
      } else if (tok == reserved[11]) {
        elsecount = ifcount;
        lex_tokens.push_back(reserved[11] + ":" + to_string(elsecount));
        ifcount--;
        tok = "";
      } else if (tok == "{") {
        block_started = true;
        condstarted = false;
        if (v != "") {
          condition += "variable:\"" + v + "\" ";
          v = "";
        }
        var_started = 0;
        if (condition != "") {
          lex_tokens.push_back(condition);
        }
        lex_tokens.push_back("opencb");
        tok = "";
        condition = "";
      } else if (tok == "}") {
        if (expr != "" and is_expr == 1) {
            lex_tokens.push_back(reserved[8] + ":(" + expr + ")");
          } else if (n != "" and is_expr == 0) {
            lex_tokens.push_back(reserved[7] + ":" + expr);
          }
          if (v != "") {
            lex_tokens.push_back(reserved[3] + ":\"" + v + "\"");
          }
          v = "";
        var_started = 0;
        n = "";
        expr = "";
        is_expr = 0;
        if (lex_tokens.back() != "opencb" and lex_tokens.back() != "sc") {
          lex_tokens.push_back("sc");
        }
        lex_tokens.push_back("closecb");
        block_started = false;
        tok = "";
      } else if (tok == reserved[0]) {
        lex_tokens.push_back(reserved[0]);
        tok = "";
      } else if (tok == "\"" or tok == "\"\"") {

        if (state == 0) {
          state = 1;
        } else if (state == 1) {
          state = 0;
          if (s == "") {
            s = "\"";
          }
          if (condstarted == false) {
            lex_tokens.push_back(reserved[1] + ":" + s + "\"");
          } else {
            condition += reserved[1] + ":" + s + "\" ";
          }
          s = "";
          tok = "";
        }
      } else if (state == 1) {
        if (tok == "\"\"") {
          s = "\"";
          lex_tokens.push_back(reserved[1] + ":" + s + "\"");
          state = 0;
          s = "";
          tok = "";
        } else {
          s += tok;
          tok = "";
        }
      } 

      if (ecount > 0) {
        exit(1);
      }
      
  }
  //cout << lex_tokens.size() << endl;
  for (i = 0; i < lex_tokens.size();i++) {
    //cout << lex_tokens[i] << endl;
  }
  return lex_tokens;
}