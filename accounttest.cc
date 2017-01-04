#include <iostream>
using namespace std;
#include "account.h"
main()
{
  account x(50);
  x += 23;
  cout << "The account has $" << x.balance << endl;
  //OUTPUT: The account has $73                                                                                        
  x -= 30;
  cout << "Now the account has $" << x.balance << endl;
  //OUTPUT: Now the account has $43                                                                                    


}

