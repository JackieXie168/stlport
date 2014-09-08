#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define search0_test main
#endif
#endif
int search0_test(int, char**)
{
  cout<<"Results of search0_test:"<<endl;
int v1[6] = { 1, 1, 2, 3, 5, 8 };
int v2[6] = { 0, 1, 2, 3, 4, 5 };
int v3[2] = { 3, 4 };

  int* location;
  location = search((int*)v1, (int*)v1 + 6, (int*)v3, (int*)v3 + 2);
  if(location == v1 + 6)
    cout << "v3 not contained in v1" << endl;
  else
    cout << "Found v3 in v1 at offset: " << location - v1 << endl;
  location = search((int*)v2, (int*)v2 + 6, (int*)v3, (int*)v3 + 2);
  if(location == v2 + 6)
    cout << "v3 not contained in v2" << endl;
  else
    cout << "Found v3 in v2 at offset: " << location - v2 << endl;
  return 0;
}
