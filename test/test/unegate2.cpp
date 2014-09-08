#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include "unary.h"

#ifdef MAIN 
#define unegate2_test main
#endif
#endif
int unegate2_test(int, char**)
{
  cout<<"Results of unegate2_test:"<<endl;

int array [3] = { 1, 2, 3 };

  int* p = find_if((int*)array, (int*)array + 3, not1(odd()));
  if(p != array + 3)
    cout << *p << endl;
  return 0;
}
