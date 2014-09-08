#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define merge0_test main
#endif
#endif
int merge0_test(int, char**)
{
  cout<<"Results of merge0_test:"<<endl;
int numbers1[5] = { 1, 6, 13, 25, 101 };
int numbers2[5] = {-5, 26, 36, 46, 99 };

  int result[10];
  merge((int*)numbers1, (int*)numbers1 + 5, (int*)numbers2, (int*)numbers2 + 5, (int*)result);
  for(int i = 0; i < 10; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
