#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define accum2_test main
#endif
#endif
static int mult(int initial_, int element_)
{
  return initial_ * element_;
}
int accum2_test(int, char**)
{
  cout<<"Results of accum2_test:"<<endl;

  vector <int> v(5);
  for(int i = 0; i < v.size(); i++)
    v[i] = i + 1;
  int prod = accumulate(v.begin(), v.end(), 1, mult);
  cout << "prod = " << prod << endl;
  return 0;
}
