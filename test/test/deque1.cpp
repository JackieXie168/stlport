#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <deque.h>
#include <algo.h>
#include <iostream.h>

#ifdef MAIN 
#define deque1_test main
#endif
#endif
int deque1_test(int, char**)
{
  cout<<"Results of deque1_test:"<<endl;
#ifdef __STL_USE_DEFALLOC				//*TY 08/06/1998 - added
  __deque__<int,allocator<int>,(size_t)3> d;		//*TY 08/06/1998 - added test for allocator<>. Note the use of this type of allocator has been a problem under previous version of STLport
#else									//*TY 08/06/1998 - added
  __deque__<int,alloc,(size_t)3> d;
#endif									//*TY 08/06/1998 - added

  d.push_back(4); // Add after end.
  d.push_back(9);
  d.push_back(16);
  d.push_front(1); // Insert at beginning.
  int i;
  for(i = 0; i < d.size(); i++)
    cout << "d[" << i << "] = " << d[i] << endl;
  cout << endl;

  d.pop_front(); // Erase first element.

  d[2] = 25; // Replace last element.
  for(i = 0; i < d.size(); i++)
    cout << "d[" << i << "] = " << d[i] << endl;
  return 0;
}
