#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define copy2_test main
#endif
#endif
int copy2_test(int, char**)
{
  cout<<"Results of copy2_test:"<<endl;
  vector <int> v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] = i;
  ostream_iterator<int> iter(cout, " ");
  copy(v.begin(), v.end(), iter);
  cout << endl;
  return 0;
}
