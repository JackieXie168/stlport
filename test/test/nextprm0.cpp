#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define nextprm0_test main
#endif
#endif
int nextprm0_test(int, char**)
{
  cout<<"Results of nextprm0_test:"<<endl;
int v1[3] = { 0, 1, 2 };

  next_permutation(v1, v1 + 3);
  for(int i = 0; i < 3; i++)
    cout << v1[i] << ' ';
  cout << endl;
  return 0;
}
