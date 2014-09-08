#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define inplmrg2_test main
#endif
#endif
int inplmrg2_test(int, char**)
{
  cout<<"Results of inplmrg2_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] =(v1.size() - i - 1) % 5;
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  inplace_merge(v1.begin(), v1.begin() + 5,
                 v1.end(),
                 greater<int>());
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  return 0;
}
