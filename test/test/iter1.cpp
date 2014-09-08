#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define iter1_test main
#endif
#endif
int iter1_test(int, char**)
{
  cout<<"Results of iter1_test:"<<endl;
  vector<const char*> v; // Vector of character strings.
  v.push_back((char*) "zippy"); // First element.
  v.push_back((char*) "motorboy"); // Second element.
  typedef vector<const char*> vec;
  vec::iterator i = v.begin(); // Position at end.
  for(i = v.begin(); i != v.end(); i++)
    cout << *i << endl; // Display item.
  return 0;
}
