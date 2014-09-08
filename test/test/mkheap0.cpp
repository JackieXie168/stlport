#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define mkheap0_test main
#endif
#endif
int mkheap0_test(int, char**)
{
  cout<<"Results of mkheap0_test:"<<endl;
int numbers[6] = { 5, 10, 4, 13, 11, 19 };

  make_heap(numbers, numbers + 6);
  for(int i = 6; i >= 1; i--)
  {
    cout << numbers[0] << endl;
    pop_heap(numbers, numbers + i);
  }
  return 0;
}
