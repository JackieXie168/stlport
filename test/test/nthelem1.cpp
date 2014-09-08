#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <stdlib.h>
#include <iostream.h>

#ifdef MAIN 
#define nthelem1_test main
#endif
#endif
int nthelem1_test(int, char**)
{
  cout<<"Results of nthelem1_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = rand() % 10;
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  nth_element(v1.begin(),
               v1.begin() + v1.size() / 2,
               v1.end());
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
