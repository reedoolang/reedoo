/* The Reedoo Language Interpreter */
/* (c) 2014 Francis McNamee. All Rights Reserved. */
/* www.reedoo.org */
/* This is my hand-made interpreter for the Reedoo Programming Language,
   I chose not to use something like lex and yacc because I didn't want to
   have to learn a new tool and be limited by what that tool can do, for
   example yacc isn't good at producing informative errors. I also enjoy the
   challenge of writting something from scratch and seeing it come to life when 
   its finished. */

/* Function Declarations */
/* We declare all of the functions up here because it makes it easy to see how many
   functions we have and it makes it easier to find inefficiencies, also it makes the
   code look nicer. */
std::vector<std::string> lex(std::string prog);