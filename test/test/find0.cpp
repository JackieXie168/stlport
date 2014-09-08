#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define find0_test main
#endif
#endif
int find0_test(int, char**)
{
  cout<<"Results of find0_test:"<<endl;
int numbers[10] = { 0, 1, 4, 9, 16, 25, 36, 49, 64 };

  int* location;
  location = find((int*)numbers, (int*)numbers + 10, 25);
  cout << "Found 25 at offset " <<(location - numbers) << endl;
  return 0;
}
