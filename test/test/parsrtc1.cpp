#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <stdlib.h>
#include <iostream.h>

#ifdef MAIN 
#define parsrtc1_test main
#endif
#endif
int parsrtc1_test(int, char**)
{
  cout<<"Results of parsrtc1_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = rand() % 10;
  vector <int> result(5);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  partial_sort_copy(v1.begin(),
                     v1.end(),
                     result.begin(),
                     result.end());
  copy(result.begin(), result.end(), iter);
  cout << endl;
  return 0;
}
