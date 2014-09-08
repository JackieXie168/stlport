#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define advance_test main
#endif
#endif
int advance_test(int, char**)
{
  cout<<"Results of advance_test:"<<endl;
  typedef vector <int> IntVector;
  IntVector v(10);
  for(int i = 0; i < v.size(); i++)
    v[i] = i;
  IntVector::iterator location = v.begin();
  cout << "At Beginning: " << *location << endl;
  advance(location, 5);
  cout << "At Beginning + 5: " << *location << endl;
  return 0;
}
