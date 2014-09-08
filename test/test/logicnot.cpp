#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define logicnot_test main
#endif
#endif
int logicnot_test(int, char**)
{
  cout<<"Results of logicnot_test:"<<endl;
bool input [7] = { 1, 0, 0, 1, 1, 1, 1 };

  int n = 0;
  count_if(input, input + 7, logical_not<bool>(), n);
  cout << "count = " << n << endl;
  return 0;
}
