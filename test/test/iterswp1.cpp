#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define iterswp1_test main
#endif
#endif
int iterswp1_test(int, char**)
{
  cout<<"Results of iterswp1_test:"<<endl;
  vector <int> v1(6);
  iota(v1.begin(), v1.end(), 0);
  iter_swap(v1.begin(), v1.begin() + 3);
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
