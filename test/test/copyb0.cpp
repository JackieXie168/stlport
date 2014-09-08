#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define copyb0_test main
#endif
#endif
int copyb0_test(int, char**)
{
  cout<<"Results of copyb0_test:"<<endl;
int numbers[5] = { 1, 2, 3, 4, 5 };

  int result[5];
  copy_backward(numbers, numbers + 5, (int*)result + 5);
  int i;
  for(i = 0; i < 5; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  for(i = 0; i < 5; i++)
    cout << result[i] << ' ';
  cout << endl;
  return 0;
}
