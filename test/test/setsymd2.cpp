#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <iostream.h>
#include <string.h>

#ifdef MAIN 
#define setsymd2_test main
#endif
#endif
int setsymd2_test(int, char**)
{
  cout<<"Results of setsymd2_test:"<<endl;
char* word1 = "ABCDEFGHIJKLMNO";
char* word2 = "LMNOPQRSTUVWXYZ";

  ostream_iterator <char> iter(cout, " ");
  cout << "word1: ";
  copy(word1, word1 + ::strlen(word1), iter);
  cout << "\nword2: ";
  copy(word2, word2 + ::strlen(word2), iter);
  cout << endl;
  set_symmetric_difference(word1, word1 + ::strlen(word1),
                            word2, word2 + ::strlen(word2),
                            iter,
                            less<char>());
  cout << endl;
  return 0;
}
