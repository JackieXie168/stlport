#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define equal0_test main
#endif
#endif
int equal0_test(int, char**)
{
  cout<<"Results of equal0_test:"<<endl;
int numbers1[5] = { 1, 2, 3, 4, 5 };
int numbers2[5] = { 1, 2, 4, 8, 16 };
int numbers3[2] = { 1, 2 };

  if(equal(numbers1, numbers1 + 5, numbers2))
    cout << "numbers1 is equal to numbers2" << endl;
  else
    cout << "numbers1 is not equal to numbers2" << endl;
  if(equal(numbers3, numbers3 + 2, numbers1))
    cout << "numbers3 is equal to numbers1" << endl;
  else
    cout << "numbers3 is not equal to numbers1" << endl;
  return 0;
}
