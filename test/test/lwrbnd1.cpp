#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <algo.h>
#include <vector.h>
#include <iostream.h>

#ifdef MAIN 
#define lwrbnd1_test main
#endif
#endif
int lwrbnd1_test(int, char**)
{
  cout<<"Results of lwrbnd1_test:"<<endl;
  vector <int> v1(20);
  for(int i = 0; i < v1.size(); i++)
  {
    v1[i] = i/4;
    cout << v1[i] << ' ';
  }
  STLPORT::vector <int>::iterator location =  lower_bound(v1.begin(), v1.end(), 3);
  cout
    << "\n3 can be inserted at index: "
    <<(location - v1.begin())
    << endl;
  return 0;
}
