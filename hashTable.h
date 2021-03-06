/*
  File name: hashTable.h
  Project: Compiler
  Author: Krishan Madan
  Email: krm219
  Class: CSE109
  Professor: James Femister
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hash.h"
//#include "hash.cc"//should I include?
#include "link.h"
//#include "link.cc"//should I 
#include <string>
#include <iostream>

#include <cstring>

using namespace std;

class HashTable{
public:
  HashTable(int n=7927);
  HashTable(const HashTable &t);
  ~HashTable();

  HashTable& add(string str, string d);

  bool inTable(string k)const;

  string& operator [](string str);

  string  operator [](string str) const;

  HashTable& operator += (string str);

  //  void remove(string str);

  friend ostream& operator<<(ostream &out,const HashTable& h);
  
private:
  int size;   //the size of the array table
  Link **table;  //dynamically allocated array of pointers, each
		 //pointer pointing to a linked list of Links or NULL

  // return true if and only iff k is a positive prime
  bool prime(int k);

  // if b is true do nothing, else display on cerr the error message and exit
  static void check(bool b, string mess);
};

#endif
