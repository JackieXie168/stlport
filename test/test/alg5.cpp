#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <deque.h>
#include <algo.h>

#ifdef MAIN 
#define alg5_test main
#endif
#endif
int alg5_test(int, char**)
{
  cout<<"Results of alg5_test:"<<endl;
  deque<int> years;
  years.push_back(1962);
  years.push_back(1992);
  years.push_back(2001);
  years.push_back(1999);
  __STD::deque<int>::iterator i;
  for(i = years.begin(); i != years.end(); i++)
    cout << *i << endl;
  return 0;
}
