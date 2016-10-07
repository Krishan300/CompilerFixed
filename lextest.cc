/*
  Test class
 */

#include "Token.h"
#include "Lexer.h"
#include <iostream>
#include <fstream>

using namespace std;

void processFile(istream& in) {
  Lexer lexer(in);
  Token token;

   token = lexer.nextToken();
  printf(" Type     Lexeme    Line #    Pos\n");
  while (token.gettype() != Token::ENDOFFILE) {
    printf("%5d     %-10s %5d  %5d\n", token.gettype(), token.getlexeme().c_str(), token.getline(), token.getposition());
    token = lexer.nextToken();
  
  }
}


int main(int argc, char **argv) {
  ifstream in;

  if (argc > 1) {
    in.open(argv[1]);
    processFile(in);
    in.close();
  } else {
    processFile(cin);
  }

}
