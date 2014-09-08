#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define copy1_test main
#endif
#endif
int copy1_test(int, char**)
{
  cout<<"Results of copy1_test:"<<endl;
char string[23] = "A string to be copied.";

  char result[23];
  copy(string, string + 23, result);
  cout << " Src: " << string << "\nDest: " << result << endl;
  return 0;
}
