/*
  File name: Hash.cc
  Author: Krishan Madan
  Email: krm219
  Class: CSE109
  Professor: James Femister
*/
#ifndef HASH_H
#define HASH_H
#include <string>
#include <stdlib.h>
using namespace std;
class Hash{
public:
  Hash(string);
  int hash() const;  //return the hash value
  private:
  int key;  
};
#endif
