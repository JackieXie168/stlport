#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define swprnge1_test main
#endif
#endif
int swprnge1_test(int, char**)
{
  cout<<"Results of swprnge1_test:"<<endl;
  char word1[] = "World";
  char word2[] = "Hello";
  cout << word1 << " " << word2 << endl;
  swap_ranges((char*)word1, (char*)word1 + ::strlen(word1), (char*)word2);
  cout << word1 << " " << word2 << endl;
  return 0;
}
