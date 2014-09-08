#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define repcpif1_test main
#endif
static bool odd(int a_)
{
  return a_ % 2;
}
#endif
int repcpif1_test(int, char**)
{
  cout<<"Results of repcpif1_test:"<<endl;

  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i % 5;
  ostream_iterator <int> iter(cout, " ");
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  vector <int> v2(v1.size());
  replace_copy_if(v1.begin(), v1.end(), v2.begin(), odd, 42);
  copy(v1.begin(), v1.end(), iter);
  cout << endl;
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  return 0;
}
