/*
  CSE 109
  Krishan Madan
  krm219
  Program Description: Header for Lexer
  Program #4
  Project:Compiler
*/
#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "Token.h"
#include <string>
using namespace std;
class Lexer
{
public:
  Lexer(istream& streamread);
  
int line;
int pos;
  int tokepos;
char ch; 
istream& storedstream;
Token nextToken();

  

private:
char nextChar();
  /*public:
  char nextChar();
  // Token nextToken();
  public:
  int line;
  int pos;
  istream& storedstream;
  Token nextToken();*/
  
  
};

#endif
