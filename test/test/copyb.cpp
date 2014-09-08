#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define copyb_test main
#endif
#endif
int copyb_test(int, char**)
{
  cout<<"Results of copyb_test:"<<endl;
  vector <int> v1(10);
  for(int i = 0; i < v1.size(); i++)
    v1[i] = i;
  vector <int> v2(v1.size());
  copy_backward(v1.begin(), v1.end(), v2.end());
  ostream_iterator<int> iter(cout, " ");
  copy(v2.begin(), v2.end(), iter);
  cout << endl;
  return 0;
}
