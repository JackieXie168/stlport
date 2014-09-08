#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>
#include <set.h>

#ifdef MAIN 
#define set1_test main
#endif
#endif
int set1_test(int, char**)
{
  cout<<"Results of set1_test:"<<endl;
  set<int, less<int> > s;
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  int count = s.erase(42);
  cout << count << " elements erased" << endl;
  return 0;
}
