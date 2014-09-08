#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define accum1_test main
#endif
#endif

int accum1_test(int, char**)
{
  cout<<"Results of accum1_test:"<<endl;
  vector <int> v(5);
  for(int i = 0; i < v.size(); i++)
    v[i] = i + 1;
  int sum = accumulate(v.begin(), v.end(), 0);
  cout << "sum = " << sum << endl;
  return 0;
}
