#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include "unary.h"

#ifdef MAIN 
#define bcompos1_test main
#endif
#endif
int bcompos1_test(int, char**)
{
  cout<<"Results of bcompos1_test:"<<endl;

int array [6] = { -2, -1, 0, 1, 2, 3 };

  binary_compose<logical_and<bool>, odd, positive> 
    b = binary_compose<logical_and<bool>, odd, positive>
(logical_and<bool>(), odd(), positive());
  int* p = find_if((int*)array, (int*)array + 6, b);
  if(p != array + 6)
    cout << *p << " is odd and positive" << endl;

  return 0;
}
