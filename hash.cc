#include "hash.h"

/*Hash::Hash(){
  }*/

Hash::Hash(string str) {
  int tmp = 0;
  int key=0;
  string p = str;
  int i;
  for(i=0; i<(int) str.length(); ++i){
    tmp += (int)str[i];
   }
  key = tmp;
}

int Hash::hash() const{
  return key;
}

