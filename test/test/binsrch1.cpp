#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define binsrch1_test main
#endif
#endif
int binsrch1_test(int, char**)
{
  cout<<"Results of binsrch1_test:"<<endl;
  int vector[100];
  for(int i = 0; i < 100; i++)
    vector[i] = i;
  if(binary_search(vector, vector + 100, 42))
    cout << "found 42" << endl;
  else
    cout << "did not find 42" << endl;
  return 0;
}
