#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <multiset.h>

#ifdef MAIN 
#define mset4_test main
#endif
#endif
int mset4_test(int, char**)
{
  cout<<"Results of mset4_test:"<<endl;
int array [] = { 3, 6, 1, 2, 3, 2, 6, 7, 9 };

  typedef multiset<int, less<int> > mset;
  mset s(array, array + 9);
  pair<mset::const_iterator, mset::const_iterator> p = s.equal_range(3);
  cout << "lower bound = " << *(p.first) << endl;
  cout << "upper bound = " << *(p.second) << endl;
  return 0;
}
