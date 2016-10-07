OPTS = -g -c -Wall -Werror

lextest: Token.o Lexer.o lextest.o 
	 g++ -o lextest *.o

Lexer.o: Lexer.cc Lexer.h Token.h
	g++ $(OPTS) Lexer.cc

Token.o: Token.cc Token.h 
	 g++ $(OPTS) Token.cc

lextest.o: lextest.cc Token.cc Lexer.cc 
	g++ $(OPTS) lextest.cc 


clean:
	rm lextest  *.o

