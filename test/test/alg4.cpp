#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define alg4_test main
#endif
#endif
int alg4_test(int, char**)
{
  cout<<"Results of alg4_test:"<<endl;
  vector<int> years;
  years.push_back(1962);
  years.push_back(1992);
  years.push_back(2001);
  years.push_back(1999);
  sort(years.begin(), years.end());
  __STD::vector<int>::const_iterator i;
  for(i = years.begin(); i != years.end(); i++)
    cout << *i << endl;
  return 0;
}
