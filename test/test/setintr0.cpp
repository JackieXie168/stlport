#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define setintr0_test main
#endif
#endif
int setintr0_test(int, char**)
{
  cout<<"Results of setintr0_test:"<<endl;
int v1[3] = { 13, 18, 23 };
int v2[4] = { 10, 13, 17, 23 };
int result[4] = { 0, 0, 0, 0 };

  set_intersection((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  for(int i = 0; i < 4; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
