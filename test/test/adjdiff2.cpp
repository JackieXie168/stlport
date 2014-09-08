#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iterator.h>
#include <iostream.h>

#ifdef MAIN 
#define adjdiff2_test main
#endif
static int mult(int a_, int b_)
{
  return a_ * b_;
}
#endif
int adjdiff2_test(int, char**)
{
  cout<<"Results of adjdiff2_test:"<<endl;

  vector <int> v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] = i + 1;
  vector <int> rslt(v.size());
  adjacent_difference(v.begin(), v.end(), rslt.begin(), mult);
  ostream_iterator<int> iter(cout, " ");
  copy(v.begin(), v.end(), iter);
  cout << endl;
  copy(rslt.begin(), rslt.end(), iter);
  cout << endl;
  return 0;
}
