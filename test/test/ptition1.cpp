#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <stdlib.h>
#include <iostream.h>

#ifdef MAIN 
#define ptition1_test main
#endif
#endif
int ptition1_test(int, char**)
{
  cout<<"Results of ptition1_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = rand() % 20;
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  partition(v1.begin(), v1.end(), bind2nd(less<int>(), 11));
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
