#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define vec4_test main
#endif
#endif
int vec4_test(int, char**)
{
  cout<<"Results of vec4_test:"<<endl;
  vector<int> v(4);
  v[0] = 1;
  v[1] = 4;
  v[2] = 9;
  v[3] = 16;
  cout << "front = " << v.front() << endl;
  cout << "back = " << v.back() << ", size = " << v.size() << endl;
  v.push_back(25);
  cout << "back = " << v.back() << ", size = " << v.size() << endl;
  v.pop_back();
  cout << "back = " << v.back() << ", size = " << v.size() << endl;
  return 0;
}
