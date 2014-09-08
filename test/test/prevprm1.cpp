#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define prevprm1_test main
#endif
#endif
int prevprm1_test(int, char**)
{
  cout<<"Results of prevprm1_test:"<<endl;
  vector <int> v1(3);
  iota(v1.begin(), v1.end(), 0);
  ostream_iterator<int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  for(int i = 0; i < 9; i++)
  {
    prev_permutation(v1.begin(), v1.end());
    copy(v1.begin(), v1.end(), iter);
    cout << endl;
  }
  return 0;
}
