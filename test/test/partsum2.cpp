#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define partsum2_test main
#endif
#endif
int partsum2_test(int, char**)
{
  cout<<"Results of partsum2_test:"<<endl;
  vector <int> v1(5);
  iota(v1.begin(), v1.end(), 1);
  vector <int> v2(v1.size());
  partial_sum(v1.begin(), v1.end(), v2.begin(), multiplies<int>());
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  return 0;
}
