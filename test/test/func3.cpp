#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define func3_test main
#endif
#endif
int func3_test(int, char**)
{
  cout<<"Results of func3_test:"<<endl;
  vector<int>v;
  v.push_back(4);
  v.push_back(1);
  v.push_back(5);
  sort(v.begin(), v.end(), greater<int>());
  __STD::vector<int>::iterator i;
  for(i = v.begin(); i != v.end(); i++)
    cout << *i << endl;
  return 0;
}
