#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define setunon0_test main
#endif
#endif
int setunon0_test(int, char**)
{
  cout<<"Results of setunon0_test:"<<endl;
int v1[3] = { 13, 18, 23 };
int v2[4] = { 10, 13, 17, 23 };
int result[7] = { 0, 0, 0, 0, 0, 0, 0 };

  set_union((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  for(int i = 0; i < 7; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
