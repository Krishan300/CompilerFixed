/*
  CSE 109
  Krishan Madan
  krm219
  Program Description: Token object
  Program #4
*/
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string>
#include "Token.h"
using namespace std;
Token::Token(int initialtype, string  initialexeme, int initline, int initpos)
{
  type=initialtype;
  lexeme=initialexeme;
  line=initline;
  pos=initpos;
  /* IDENT=1;
  INTLIT=2;
  STRINGLIT=3;
  PLUS=4;
  MINUS=5;
  TIMES=6;
  DIVIDE=7;
  ASSIGN=8;
  EQ=9;
  NE=10;
  LT=11;
  LE=12
  GT=13;
  GE=14;
  AND=15;
  OR=16;
  LPAREN=17;
  RPAREN=18;
  LBRACE=19;
  RBRACE=20;
  COMMA=21;
  SEMICOLON=22;
  IF=23;
  ELSE=24;
  WHIE=25;
  FUNCTION=26;
  VAR=27;
  PRINTF=28;
  RETURN=29;
  ENDOFFILE=30;
  ERROR=31;*/
  
}

int Token:: gettype(){
  return type;
}

string Token::getlexeme(){
  return lexeme;
}

int Token::getline()
{
  return line;
}

int Token:: getposition(){

  return pos;
}
