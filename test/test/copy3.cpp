#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define copy3_test main
#endif
#endif
int copy3_test(int, char**)
{
  cout<<"Results of copy3_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i;
  vector <int> v2(10);
  copy(v1.begin(), v1.end(), v2.begin());
  ostream_iterator<int> iter(cout, " ");
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  return 0;
}
