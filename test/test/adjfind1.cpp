#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define adjfind1_test main
#endif
#endif
int adjfind1_test(int, char**)
{
  cout<<"Results of adjfind1_test:"<<endl;
  typedef vector<int> IntVector;
  IntVector v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] = i;
  IntVector::iterator location;
  location = adjacent_find(v.begin(), v.end());
  if(location != v.end())
    cout << "Found adjacent pair of: " << *location << endl;
  else
    cout << "No adjacent pairs" << endl;
  v[6] = 7;
  location = adjacent_find(v.begin(), v.end());
  if(location != v.end())
    cout << "Found adjacent pair of: " << *location << endl;
  else
    cout << "No adjacent pairs" << endl;
  return 0;
}
