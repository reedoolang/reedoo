CC = c++
CXXFLAGS  = -std=c++11

all: r

r: reedoo.o lexer.o parser.o variables.o eval.o io.o
	$(CC)	$(CXXFLAGS)	reedoo.o	lexer.o 	parser.o 	variables.o		eval.o 	io.o	-o	r

io.o: io.cc io.h
	$(CC)	$(CXXFLAGS) -c	io.cc

eval.o: eval.cc eval.h
	$(CC)	$(CXXFLAGS) -c	eval.cc

variables.o: variables.cc variables.h
	$(CC)	$(CXXFLAGS) -c	variables.cc

parser.o: parser.cc parser.h
	$(CC)	$(CXXFLAGS) -c	parser.cc

lexer.o: lexer.cc lexer.h
	$(CC)	$(CXXFLAGS) -c	lexer.cc

reedoo.o: reedoo.cc reedoo.h
	$(CC)	$(CXXFLAGS) -c	reedoo.cc

clean:
	rm -rf *o reedoo

cleanw:
	del *.o