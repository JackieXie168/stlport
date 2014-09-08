#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define copy4_test main
#endif
#endif
int copy4_test(int, char**)
{
  cout<<"Results of copy4_test:"<<endl;
  typedef vector<int> IVec;
  vector<int> v1(10);
  for(int loc = 0; loc < v1.size(); loc++)
    v1[loc] = loc;
  vector<int> v2;
  insert_iterator<IVec> i(v2, v2.begin());
  copy(v1.begin(), v1.end(), i);
  ostream_iterator<int> outIter(cout, " ");
  copy(v2.begin(), v2.end(), outIter);
  cout << endl;
  return 0;
}
