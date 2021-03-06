/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */


/* Function Declarations */
/* We declare all of the functions up here because it makes it easy to see how many
   functions we have and it makes it easier to find inefficiencies, also it makes the
   code look nicer. */
void exec_program();

std::string load_program();

/* Definitions */
/* These are our constants, these are defined as constant at the start of the program so
   that if anything goes wrong in the execution of the code we can always display the
   right kind of errors. */
#define IO_ERROR "[IO ERROR] "
#define SYNTAX_ERROR "[SYNTAX ERROR] "
#define ASSIGN_ERROR "[ASSIGN ERROR] "