#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define swap1_test main
#endif
#endif
int swap1_test(int, char**)
{
  cout<<"Results of swap1_test:"<<endl;
  int a = 42;
  int b = 19;
  cout << "a = " << a << " b = " << b << endl;
  swap(a, b);
  cout << "a = " << a << " b = " << b << endl;
  return 0;
}
