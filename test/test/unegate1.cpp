#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include "unary.h"

#ifdef MAIN 
#define unegate1_test main
#endif
#endif
int unegate1_test(int, char**)
{
  cout<<"Results of unegate1_test:"<<endl;

int array [3] = { 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 3, unary_negate<odd>(odd()));
  if(p != array + 3)
    cout << *p << endl;
  return 0;
}
