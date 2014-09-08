#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define replif1_test main
#endif
static bool odd(int a_)
{
  return a_ % 2;
}
#endif
int replif1_test(int, char**)
{
  cout<<"Results of replif1_test:"<<endl;

  vector <int> v1(10);
  int i;
  for(i = 0; i < v1.size(); i++)
  {
    v1[i] = i % 5;
    cout << v1[i] << ' ';
  }
  cout << endl;
  replace_if(v1.begin(), v1.end(), odd, 42);
  for(i = 0; i < v1.size(); i++)
    cout << v1[i] << ' ';
  cout << endl;
  return 0;
}
