#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define func1_test main
#endif
#endif
static bool bigger(int i_)
{
  return i_ > 3;
}
int func1_test(int, char**)
{
  cout<<"Results of func1_test:"<<endl;

  vector<int>v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  int n = 0;
  count_if(v.begin(), v.end(), bigger, n);
  cout << "Number greater than 3 = " << n << endl;
  return 0;
}
