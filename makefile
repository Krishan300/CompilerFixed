OPTS = -g -c -Wall -Werror

microc: Token.o Lexer.o microc.o parser.o  
	g++ -o microc *.o

Lexer.o: Lexer.cc Lexer.h Token.h
	g++ $(OPTS) Lexer.cc

Token.o: Token.cc Token.h 
	g++ $(OPTS) Token.cc

lextest.o: lextest.cc Token.cc Lexer.cc 
	g++ $(OPTS) lextest.cc 

parser.o: parser.cc parser.h 
	g++ $(OPTS) parser.cc

clean:
	rm microc *.o

