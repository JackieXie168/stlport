#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define iter4_test main
#endif
#endif
int iter4_test(int, char**)
{
  cout<<"Results of iter4_test:"<<endl;
  vector<int> v; // Empty vector of integers.
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  // Position immediately after last item.
  STLPORT::vector<int>::iterator i = v.end(); 
  // Move back one and then access.
  cout << "last element is " << *--i << endl; 
  i -= 2; // Jump back two items.
  cout << "first element is " << *i << endl;
  return 0;
}
