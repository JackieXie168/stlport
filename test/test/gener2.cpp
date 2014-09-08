#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <stdlib.h>
#include "fib.h"

#ifdef MAIN 
#define gener2_test main
#endif
#endif

int gener2_test(int, char**)
{
  cout<<"Results of gener2_test:"<<endl;
  vector <int> v1(10);
  Fibonacci generator;
  generate(v1.begin(), v1.end(), generator);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
