#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <vector.h>
#include <algo.h>

#ifdef MAIN 
#define vec5_test main
#endif
#endif
int vec5_test(int, char**)
{
  cout<<"Results of vec5_test:"<<endl;
int array [] = { 1, 4, 9, 16 };

  vector<int> v(array, array + 4);
  for(int i = 0; i < v.size(); i++)
    cout << "v[" << i << "] = " << v[i] << endl;
  return 0;
}
