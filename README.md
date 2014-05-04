Some stuff about Reedoo
=======================

The source code of the Reedoo Programming Langauge. Reedoo is a brand new kind of programming language that aims to be everything that great language should be. The aims of Reedoo are:
  1. A language that is fast, safe and secure
  2. Something that is fun to program in and easy to learn
  3. Work across all major platforms on all major processor architectures
  4. Have a large standard library
  5. Be open source to allow anyone to help or even just see how it works.


So how does Reedoo work?
========================

Reedoo programs are executed using the Reedoo Virtual Machine. The Reedoo language is implemented in C++11. Reedoo was originally implemented in RPython but was rewritten in C++ due to the fact the RPython has almost no documentation which made it difficult to use. Also, by using C++11 instead we can compile Reedoo with just a C++ compiler that supports the C++11 standard. Since Reedoo is written in C++11 the hope is that Reedoo will be one of the fastest languages around when it's ready.

Reedoo source code is stored in .rd files. The .rd files are converted into .rda files by the Reedoo Compiler. Then the .rda files are passed to the Reedoo Assembler where they are converted into .rdc files, which can be executed by the Reedoo Virtual Machine.

For more information about Reedoo, in its current state go to: http://www.reedoo.org

Reedoo will be open source once it is complete enough for an alpha release. Until then this repository will be empty. To find out when Reedoo will be available go to: http://www.reedoo.org
