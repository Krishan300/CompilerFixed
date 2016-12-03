/*
 File name: microc.cc
 Description: executable 
 Project: Compiler
 Author: Krishan Madan
 Email: krm219
 Class: CSE109
 Professor: James Femister
*/


#include "Token.h"
#include "Lexer.h"
#include "parser.h"
#include <iostream>
#include <fstream>

using namespace std;

void processFile(istream& in) {
  Lexer lexer(in);
  Token token;
  Parser parser(lexer, cout);
   Parser::TreeNode* program = parser.compilationUnit();
   // cout << Parser::TreeNode::toString(program) << endl;
    parser.genasm(program);
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
  return 0;
  
}
