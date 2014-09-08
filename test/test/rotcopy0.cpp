#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define rotcopy0_test main
#endif
#endif
int rotcopy0_test(int, char**)
{
  cout<<"Results of rotcopy0_test:"<<endl;
int numbers[6] = { 0, 1, 2, 3, 4, 5 };

  int result[6];
  rotate_copy((int*)numbers, (int*)numbers + 3, (int*)numbers + 6, (int*)result);
  for(int i = 0; i < 6; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
