/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */
/* This is my hand-made interpreter for the Reedoo Programming Language,
   I chose not to use something like lex and yacc because I didn't want to
   have to learn a new tool and be limited by what that tool can do, for
   example yacc isn't good at producing informative errors. I also enjoy the
   challenge of writting something from scratch and seeing it come to life when 
   its finished. */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "reedoo.h"
#include "lexer.h"
#include "parser.h"
#include "eval.h"
#include "io.h"

/* Global Variables */
/* Not all of these are actual "keywords" that can be used in programs.
   They are called keywords because they are reserved, either because they
   are specified as keywords in the grammar or because they are reserved by
   the interpreter for internal use. */
std::string keywords[10] = { "print", "string", "sc", "variable", "eq", "undefined", "nl", "num", "expr", "eof" };
/* We store tokens in a vector, we could use an array but specifying an arrays
   size at runtime is technically impossible and the work arounds are a pain. */

/* Our "symbol table" is just a vector too because, we can only determine how
   large the symbol table should be at runtime, so we use a vector to make things
   easier. */

std::vector<std::string> tokens;

int linenum = 0;
int errcount = 0;

using namespace std;

/* We load the program into the interpreter by reading the file */
string load_program(string filename) {

  string filedata;

    ifstream rdfile(filename);
    /* We check to see whether or not we can open the file. This doesn't tell use whether
       the file exists because permissions could also prevent us being able to open the file. */
    if (!rdfile) {
      cout << IO_ERROR << "Unable to open the file \"" << filename << "\"." << endl;
      exit(0);
    }
    /* Loop through and grab each line of the file, then store each line in filedata. */
    for (std::string line; std::getline(rdfile, line); )
    {
        filedata += line;
        filedata += "\n";
    }

    /* Close the file when we're done. */
    rdfile.close();

    /* Return the data so that the rest of the program can use it. */
    return filedata;                       
}

/* Main program exec function */
void exec_program(string filename) {
  tokens = lex(load_program(filename));
  parse(tokens);
}

/* The main function, we have to start somewhere. */
int main(int argc, char* argv[]) {

  if (!argv[1]) {
   cout << "Usage: reedoo <filename> [args]" << endl;
  } else {
   exec_program(argv[1]);
  }
  return 0;
}