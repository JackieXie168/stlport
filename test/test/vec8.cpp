#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define vec8_test main
#endif
#endif
int vec8_test(int, char**)
{
  cout<<"Results of vec8_test:"<<endl;
  vector<int> v;
  cout << "capacity = " << v.capacity() << endl;
  v.push_back(42);
  cout << "capacity = " << v.capacity() << endl;
  v.reserve(5000);
  cout << "capacity = " << v.capacity() << endl;
  return 0;
}
