#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define findif0_test main
#endif
static bool odd(int a_)
{
  return a_ % 2;
}
#endif
int findif0_test(int, char**)
{
  cout<<"Results of findif0_test:"<<endl;

int numbers[6] = { 2, 4, 8, 15, 32, 64 };

  int* location = find_if((int*)numbers, (int*)numbers + 6, odd);
  if(location != numbers + 6)
    cout
      << "Value "
      << *location
      << " at offset "
      <<(location - numbers)
      << " is odd"
      << endl;
  return 0;
}
