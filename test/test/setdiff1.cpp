#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define setdiff1_test main
#endif
#endif
int setdiff1_test(int, char**)
{
  cout<<"Results of setdiff1_test:"<<endl;
  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  vector <int> v2(10);
  iota(v2.begin(), v2.end(), 7);
  ostream_iterator <int> iter(cout, " ");
  cout << "v1: ";
  copy(v1.begin(), v1.end(), iter);
  cout << "\nv2: ";
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), iter);
  cout << endl;
  return 0;
}
