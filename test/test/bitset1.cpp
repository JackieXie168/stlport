#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <bitset>
#include <algo.h>

#ifdef MAIN 
#define bitset1_test main
#endif
#endif
int bitset1_test(int, char**)
{
  cout<<"Results of bitset1_test:"<<endl;
  __STLPORT_STD::bitset<13U> b1(0xFFFF);
  __STLPORT_STD::bitset<13U> b2(0x1111);
  cout << "b1 size = " << b1.size() << endl;
# if !defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
  cout << "b1 = "<<b1<<endl;
# else
  cout << "b1 = "<<b1.to_string()<<endl;
# endif
  cout << "b2 size = " << b2.size() << endl;
# if defined (__STL_NON_TYPE_TMPL_PARAM_BUG)
  cout << "b2 = "<<b2.to_string()<<endl;
# else
  cout << "b2 = "<<b2<<endl;
# endif
  b1 = b1^(b2<<2);
# ifdef __STL_NON_TYPE_TMPL_PARAM_BUG
  cout << "b1 = "<<b1.to_string()<<endl;
# else
  cout << "b1 = "<<b1<<endl;
# endif
  return 0;
}
