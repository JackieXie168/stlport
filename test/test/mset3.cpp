#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <multiset.h>

#ifdef MAIN 
#define mset3_test main
#endif
#endif
int mset3_test(int, char**)
{
  cout<<"Results of mset3_test:"<<endl;
int array [] = { 3, 6, 1, 2, 3, 2, 6, 7, 9 };

  multiset<int, less<int> > s(array, array + 9);
  __STD::multiset<int, less<int> >::iterator i;
  i = s.lower_bound(3);
  cout << "lower bound = " << *i << endl;
  i = s.upper_bound(3);
  cout << "upper bound = " << *i << endl;
  return 0;
}
