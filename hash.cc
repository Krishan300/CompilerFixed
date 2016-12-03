/*
File name: Hash.cc
Author: Krishan Madan
Email: krm219
Class: CSE109
Professor: James Femister
class was given-not written
*/

#include "hash.h"

/*Hash::Hash(){
  }*/

Hash::Hash(string str) {
 
    int tmp = 0;
    const char *p = str.c_str();
    while(*p) {
      tmp += *p++;
    }
    key = abs(tmp);
 
 }

int Hash::hash() const{
  return key;
}

