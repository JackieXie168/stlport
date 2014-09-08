#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define nextprm1_test main
#endif
#endif
int nextprm1_test(int, char**)
{
  cout<<"Results of nextprm1_test:"<<endl;
  vector <int> v1(3);
  iota(v1.begin(), v1.end(), 0);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  for(int i = 0; i < 9; i++)
  {
    next_permutation(v1.begin(), v1.end());
    copy(v1.begin(), v1.end(), iter);
    cout << endl;
  }
  return 0;
}
