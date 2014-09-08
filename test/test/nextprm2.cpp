#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define nextprm2_test main
#endif
#endif
int nextprm2_test(int, char**)
{
  cout<<"Results of nextprm2_test:"<<endl;
  vector <char> v1(3);
  iota(v1.begin(), v1.end(), 'A');
  ostream_iterator<char> iter(cout);
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  for(int i = 0; i < 9; i++)
  {
    next_permutation(v1.begin(), v1.end(), less<char>());
    copy(v1.begin(), v1.end(), iter);
    cout << endl;
  }
  return 0;
}
