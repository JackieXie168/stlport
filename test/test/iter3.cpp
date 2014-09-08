#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef __STL_USE_NAMESPACES
using namespace std;
#endif

#ifdef MAIN 
#define iter3_test main
#endif
#endif
int iter3_test(int, char**)
{
  cout<<"Results of iter3_test:"<<endl;
  typedef vector<const char*> Vec;
  Vec v; // Vector of character strings.
  v.push_back((char*) "zippy"); // First element.
  v.push_back((char*) "motorboy"); // Second element.
  Vec::reverse_iterator it;
  for(it = v.rbegin(); it != v.rend(); it++)
    cout << *it << endl; // Display item.
  return 0;
}
