#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define func2_test main
#endif
#endif
static bool bigger_than(int x_, int y_)
{
  return x_ > y_;
}
int func2_test(int, char**)
{
  cout<<"Results of func2_test:"<<endl;

  vector<int>v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  sort(v.begin(), v.end(), bigger_than);
  __STD::vector<int>::iterator i;
  for(i = v.begin(); i != v.end(); i++)
    cout << *i << endl;
  return 0;
}
