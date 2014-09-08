#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algobase.h>
# include <defalloc.h>

#ifdef MAIN 
#define rawiter_test main
#endif
#include "rawiter.hpp"
#endif

int rawiter_test(int, char**)
{
  cout<<"Results of rawiter_test:"<<endl;

  allocator<X> a;
  STLPORT::allocator<X>::pointer save_p, p = a.allocate(5); 
  save_p=p;
  raw_storage_iterator<X*, X> r(p);
  int i;
  for(i = 0; i < 5; i++)
    *r++ = X(i);
  for(i = 0; i < 5; i++)
    cout << *p++ << endl;
# ifdef __SGI_STL_PORT
  a.deallocate(save_p,5);
# else
  a.deallocate(save_p);
# endif
  return 0;
}
