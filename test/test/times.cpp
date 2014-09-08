#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define times_test main
#endif
#endif
int times_test(int, char**)
{
  cout<<"Results of times_test:"<<endl;
int input [4] = { 1, 5, 7, 2 };

  int total = accumulate(input, input + 4, 1, multiplies<int>());
  cout << "total = " << total << endl;
  return 0;
}
