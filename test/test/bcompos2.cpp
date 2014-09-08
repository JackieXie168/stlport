#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include "unary.h"

#ifdef MAIN 
#define bcompos2_test main
#endif
#endif
int bcompos2_test(int, char**)
{
  cout<<"Results of bcompos2_test:"<<endl;

int array [6] = { -2, -1 , 0, 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 6, 
    compose2(logical_and<bool>(), odd(), positive()));
  if(p != array + 6)
    cout << *p << " is odd and positive" << endl;
  return 0;
}
