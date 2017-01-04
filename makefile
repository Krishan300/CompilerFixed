 OPTS = -g -c -Wall -Werror

microc: Token.o Lexer.o microc.o parser.o SymbolTable.o stack.o hashTable.o link.o hash.o      
	g++ -o microc *.o

Lexer.o: Lexer.cc Lexer.h Token.h
	g++ $(OPTS) Lexer.cc

Token.o: Token.cc Token.h 
	g++ $(OPTS) Token.cc

parser.o: parser.cc parser.h hash.h SymbolTable.h hashTable.h Lexer.h Token.h    
	g++ $(OPTS) parser.cc

SymbolTable.o : SymbolTable.cc SymbolTable.h stack.h hashTable.h     
	g++ $(OPTS) SymbolTable.cc

stack.o: stack.cc stack.h hashTable.h
	g++ $(OPTS) stack.cc

hashTable.o: hashTable.cc hashTable.h link.h hash.h 
	g++ $(OPTS) hashTable.cc

link.o: link.cc link.h
	g++ $(OPTS) link.cc

hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc 


clean:
	rm microc *.o

