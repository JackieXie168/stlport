#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define revcopy1_test main
#endif
#endif
int revcopy1_test(int, char**)
{
  cout<<"Results of revcopy1_test:"<<endl;
int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  int result[6];
  reverse_copy((int*)numbers, (int*)numbers + 6, (int*)result);
  int i;
  for(i = 0; i < 6; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  for(i = 0; i < 6; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
