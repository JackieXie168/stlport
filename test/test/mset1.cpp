#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <multiset.h>
#include <set.h>

#ifdef MAIN 
#define mset1_test main
#endif
  typedef multiset<int, less<int> > mset;
#endif
int mset1_test(int, char**)
{
  cout<<"Results of mset1_test:"<<endl;
  mset s;
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  s.insert(42);
  cout << "count(42) = " << s.count(42) << endl;
  __STD::set<int, less<int> >::iterator i = s.find(40);
  if(i == s.end())
    cout << "40 Not found" << endl;
  else
    cout << "Found " << *i << endl;
  i = s.find(42);
  if(i == s.end())
    cout << "Not found" << endl;
  else
    cout << "Found " << *i << endl;
  int count = s.erase(42);
  cout << "Erased " << count << " instances" << endl;
  return 0;
}
