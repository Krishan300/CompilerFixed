/*
File name: symbolTable.cc
Description:generates Unique Symbols
Project: Compiler
Author: Krishan Madan
Email: krm219
Class: CSE109
Professor: James Femister
*/

#include "SymbolTable.h"
#include <string>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <iostream>

using namespace std;

SymbolTable::SymbolTable(int n)
{
   mainTable=Stack(n);
}

void SymbolTable::  enterScope(){
  HashTable currentScope(101);
  mainTable.push(currentScope);     
}

void SymbolTable:: exitScope(){
  mainTable.pop();
}

int SymbolTable:: addSymbol(string symbolname){
  //  cout<<symbolname.c_str()<<endl;
  // cout<<symbolname<<endl;
  HashTable &topostack=mainTable.peek();
  int preexistingsymbols=0;
  int retvalue;
  // const char *sn=symbolname.c_str();
     if(!topostack.inTable(symbolname))
       {
	 retvalue=1;
	 // string lastuniquesymbol=getUniqueSymbol(symbolname);
	         int i;
                 for(i=mainTable.gettosindex();i>=0;--i)
	         {
		   // cout<<mainTable[i]<<endl;
		   if(mainTable[i].inTable(symbolname))
		     {
                       preexistingsymbols=preexistingsymbols+1;
		       // cout<<preexistingsymbols<<endl;
		     }
	         }
		 string preexistingsymbolsst=itos(preexistingsymbols+1);
		 preexistingsymbolsst=symbolname+"$"+preexistingsymbolsst;
		 
		topostack.add(symbolname, preexistingsymbolsst);
              }
     
        else{

       retvalue=0;
       }
	     
     return retvalue;
    }


string SymbolTable:: getUniqueSymbol(string symbolname){
  string retstring=" ";
  // HashTable topostack=mainTable.peek();
  // const char *sn=symbolname.c_str();
  int i;
  // cout<<mainTable.gettosindex()<<endl;
  for(i=mainTable.gettosindex(); i>=0;--i)
    {
      //cout<<i<<endl;
      // cout<<"i like cheese"<<endl;
      if(mainTable[i].inTable(symbolname))
	{
	  // cout<<"bob"<<endl;
          retstring=mainTable[i][symbolname];
	  break; 
        }
    }
  return retstring;
  }




string SymbolTable:: itos(int i)
{ stringstream ss; ss << i; string res = ss.str(); return res;}





