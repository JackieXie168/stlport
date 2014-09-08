#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define prevprm0_test main
#endif
#endif
int prevprm0_test(int, char**)
{
  cout<<"Results of prevprm0_test:"<<endl;
int v1[3] = { 0, 1, 2 };

  prev_permutation(v1, v1 + 3);
  for(int i = 0; i < 3; i++)
    cout << v1[i] << ' ';
  cout << endl;
  return 0;
}
