#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define setunon2_test main
#endif
#endif
int setunon2_test(int, char**)
{
  cout<<"Results of setunon2_test:"<<endl;
char* word1 = "ABCDEFGHIJKLMNO";
char* word2 = "LMNOPQRSTUVWXYZ";

  ostream_iterator <char> iter(cout, " ");
  cout << "word1: ";
  copy(word1, word1 + ::strlen(word1), iter);
  cout << "\nword2: ";
  copy(word2, word2 + ::strlen(word2), iter);
  cout << endl;
  set_union(word1, word1 + ::strlen(word1),
             word2, word2 + ::strlen(word2),
             iter,
             less<char>());
  cout << endl;
  return 0;
}
