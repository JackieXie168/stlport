#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <stdlib.h>

#include "fadapter.h"

#ifdef MAIN 
#define gener1_test main
#endif
#endif

#if defined(__IBMCPP__) // hputman: Add for IBM VisualAge
#define CXXRAND_SCOPE static
#else
#define CXXRAND_SCOPE
#endif  


CXXRAND_SCOPE  int cxxrand() { return rand();}

int gener1_test(int, char**)
{
  cout<<"Results of gener1_test:"<<endl;
  int numbers[10];
#if defined(__MVS__)
  generate(numbers, numbers + 10, ptr_gen(cxxrand));
#else
  generate(numbers, numbers + 10, cxxrand);
#endif

  for(int i = 0; i < 10; i++)
    cout << numbers[i] << ' ';
  cout << endl;
  return 0;
}
