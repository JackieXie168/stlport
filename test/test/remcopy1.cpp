#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define remcopy1_test main
#endif
#endif
int remcopy1_test(int, char**)
{
  cout<<"Results of remcopy1_test:"<<endl;
int numbers[6] = { 1, 2, 3, 1, 2, 3 };
int result[6] = { 0, 0, 0, 0, 0, 0 };

  remove_copy((int*)numbers, (int*)numbers + 6, (int*)result, 2);
  for(int i = 0; i < 6; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
