#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define setdiff0_test main
#endif
#endif
int setdiff0_test(int, char**)
{
  cout<<"Results of setdiff0_test:"<<endl;
int v1[3] = { 13, 18, 23 };
int v2[4] = { 10, 13, 17, 23 };
int result[4] = { 0, 0, 0, 0 };

  set_difference((int*)v1, (int*)v1 + 3, (int*)v2, (int*)v2 + 4, (int*)result);
  int i;
  for(i = 0; i < 4; i++)
    cout << result[i] << ' ';
  cout << endl;
  set_difference((int*)v2, (int*)v2 + 4, (int*)v1, (int*)v1 + 2, (int*)result);
  for(i = 0; i < 4; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
