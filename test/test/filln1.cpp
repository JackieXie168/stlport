#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define filln1_test main
#endif
#endif
int filln1_test(int, char**)
{
  cout<<"Results of filln1_test:"<<endl;
  vector <int> v(10);
  fill_n(v.begin(), v.size(), 42);
  for(int i = 0; i < 10; i++)
    cout << v[i] << ' ';
  cout << endl;
  return 0;
}
