#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define merge1_test main
#endif
#endif
int merge1_test(int, char**)
{
  cout<<"Results of merge1_test:"<<endl;
  vector <int> v1(5);
  vector <int> v2(v1.size());
  iota(v1.begin(), v1.end(), 0);
  iota(v2.begin(), v2.end(), 3);
  vector <int> result(v1.size() + v2.size());
  merge(v1.begin(), v1.end(), v2.begin(), v2.end(), result.begin());
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  copy(result.begin(), result.end(), iter);
  cout << endl;
  return 0;
}
