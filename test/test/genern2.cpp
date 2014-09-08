#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <stdlib.h>
#include "fib.h"

#ifdef MAIN 
#define genern2_test main
#endif
#endif
int genern2_test(int, char**)
{
  cout<<"Results of genern2_test:"<<endl;

  vector <int> v1(10);
  Fibonacci generator;
  generate_n(v1.begin(), v1.size(), generator);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
