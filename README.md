What is Reedoo?
===============

The source code of the Reedoo Programming Langauge. Reedoo is a brand new kind of programming language that aims to be everything that great language should be. The aims of Reedoo are:
  1. A language that is fast, safe and secure
  2. Something that is fun to program in and easy to learn
  3. Work across all major platforms on all major processor architectures
  4. Have a large standard library
  5. Be open source to allow anyone to help or even just see how it works.

Reedoo's Syntax
===============
Reedoo's syntax has been influenced by a number of other popular and widely used programming languages. Reedoo follows the conventional approach to separating code blocks using curly-brackets. ( { } )

Variables in Reedoo are prepended with a percent-sign ( % ). Just like PHP prepends variables with the dollar-sign ( $ ).

Unlike PHP however, semi-colons at the end of statements are optional. If semi-colons are left out then the Reedoo Interpreter's Lexer will inject semi-colons at each newline it sees in the source file.

Reedoo can also evaluate expressions containing brackets, addition, subtraction, division and multiplication. There will be a mod() function for modulus calculations as the percent-sign is reserved for variable names.

A simple walkthrough
====================

To print text in Reedoo you can use the 'print' keyword. Here's an example,
```perl
print "Hello World"
```

In Reedoo semi-colons are optional as they are injected by the lexer if they're missing.

Assigning variables in Reedoo is similar to PHP, just change the dollar-sign to a percent-sign. Here's an example,
```perl
%test = "This is a variable"
print %test
```

Reedoo also has 'if' statements, if statements in Reedoo are inspired by 'if' statements in C-like, languages. Reedoo's 'if' statements are most similar to those in Go.
```perl
if %test == "This is a variable" {
	
	print "The condition is true."

}
```

Thanks to semi-colon injection, as in Go, the opening curly bracket must be on the same line as the if keyword and the condition. If statements, since they are statements can also end with a semi-colon, but like other statements it's optional.

So how does Reedoo work?
========================

Reedoo programs are executed using the Reedoo Virtual Machine. The Reedoo language is implemented in C++11. Reedoo was originally implemented in RPython but was rewritten in C++ due to the fact the RPython has almost no documentation which made it difficult to use. Also, by using C++11 instead we can compile Reedoo with just a C++ compiler that supports the C++11 standard. Since Reedoo is written in C++11 the hope is that Reedoo will be one of the fastest languages around when it's ready.

For more information about Reedoo, in its current state go to: http://www.reedoo.org

Reedoo will be open source once it is complete enough for an alpha release. Until then this repository will be empty. To find out when Reedoo will be available go to: http://www.reedoo.org
