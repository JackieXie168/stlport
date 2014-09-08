#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define fill1_test main
#endif
#endif
int fill1_test(int, char**)
{
  cout<<"Results of fill1_test:"<<endl;
  vector <int> v(10);
  fill(v.begin(), v.end(), 42);
  for(int i = 0; i < 10; i++)
    cout << v[i] << ' ';
  cout << endl;
  return 0;
}
