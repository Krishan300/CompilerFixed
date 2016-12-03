/*
  CSE 109
  Krishan Madan
  krm219
  Program Description: Header file for Token
  Program #4
*/
#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <cstdlib>
#include <stdio.h>
//#include "Link.h"
#include <string>
using namespace std;
class Token{
public:
int gettype();
string getlexeme();
int getline();
int getposition();
static const int IDENT=1;
static const int INTLIT=2;
static const int  STRINGLIT=3;
static const int PLUS=4;
static const int MINUS=5;
  static const int TIMES=6;
  static const int DIVIDE=7;
  static const int ASSIGN=8;
  static const int EQ=9;
  static const int NE=10;
  static const int LT=11;
  static const int LE=12;
  static const int GT=13;
  static const int GE=14;
  static const int AND=15;
  static const int OR=16;
  static const int LPAREN=17;
  static const int RPAREN=18;
  static const int LBRACE=19;
  static const int RBRACE=20;
  static const int COMMA=21;
  static const int SEMICOLON=22;
  static const int IF=23;
  static const int ELSE=24;
  static const int WHILE=25;
  static const int FUNCTION=26;
  static const int VAR=27;
  static const int PRINTF=28;
  static const int RETURN=29;
  static const int ENDOFFILE=30;
  static const int ERROR=31;
  
Token(int initialtype, string initiallexeme, int initline, int initpos);
  Token(){};
 private:
 int type;
 string lexeme;
 int line;
 int pos;

 
};
#endif
