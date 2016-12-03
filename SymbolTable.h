/*
 File name: symbolTable.h
 Description:header for SymbolTable
 Project: Compiler
 Author: Krishan Madan
 Email: krm219
 Class: CSE109
 Professor: James Femister
*/


#ifndef SymbolTable_H
#define SymbolTable_H
#include <iostream>
//#include "hashTable.h"
//#include "stack.cc"//temporary fix
#include "hashTable.h"
#include "stack.h"

#include <map>
//#include "hash.h"
#include <sstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iostream>

using namespace std;

//class hashTable;
class SymbolTable {

public:
SymbolTable(int n=101);

 

void enterScope(); 

void exitScope();

int addSymbol(string symbolname);

string getUniqueSymbol(string symbolname);

string itos(int i);

Stack mainTable;
};

#endif
