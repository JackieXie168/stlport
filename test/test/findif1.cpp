#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define findif1_test main
#endif
#endif
static bool div_3(int a_)
{
  return a_ % 3 ? 0 : 1;
}
int findif1_test(int, char**)
{
  cout<<"Results of findif1_test:"<<endl;

  typedef vector <int> IntVec;
  IntVec v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] =(i + 1) *(i + 1);
  IntVec::iterator iter;
  iter = find_if(v.begin(), v.end(), div_3);
  if(iter != v.end())
    cout
      << "Value "
      << *iter
      << " at offset "
      <<(iter - v.begin())
      << " is divisible by 3"
      << endl;
  return 0;
}
