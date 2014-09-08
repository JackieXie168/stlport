#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define rotate1_test main
#endif
#endif
int rotate1_test(int, char**)
{
  cout<<"Results of rotate1_test:"<<endl;
  vector <int> v1(10);
  iota(v1.begin(), v1.end(), 0);
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  for(int i = 0; i < v1.size(); i++)
  {
    rotate(v1.begin(), v1.begin() + i, v1.end());
    ostream_iterator <int> iter(cout, " ");
    copy(v1.begin(), v1.end(), iter);
    cout << endl;
  }
  cout << endl;
  return 0;
}
