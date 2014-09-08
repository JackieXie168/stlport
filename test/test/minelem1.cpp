#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define minelem1_test main
#endif
#endif
int minelem1_test(int, char**)
{
  cout<<"Results of minelem1_test:"<<endl;
int numbers[6] = { -10, 15, -100, 36, -242, 42 };

  cout << *min_element((int*)numbers, (int*)numbers + 6) << endl;
  return 0;
}
