#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <vector.h>
#include <algo.h>
#include <iostream.h>
#include <stdlib.h>

#include "fadapter.h"

#ifdef MAIN 
#define genern1_test main
#endif
#endif

#if defined (__MVS__)	\
 || (defined(__SC__) && __SC__ >= 0x882) || defined(__MRC__)		//*TY 07/18/98 - added  Apple SCpp and MrCpp
  int cxxrand() { return rand();}
#endif

int genern1_test(int, char**)
{
  cout<<"Results of genern1_test:"<<endl;

#ifndef __STL_MEMBER_POINTER_PARAM_BUG		//*TY 07/18/98 - added conditional
											// since ptr_gen() is not defined under this condition 
											// (see xfunction.h)
  vector <int> v1(10);
#if defined (__MVS__)	\
 || (defined(__SC__) && __SC__ >= 0x882) || defined(__MRC__)		//*TY 07/18/98 - added  Apple SCpp and MrCpp
  generate_n(v1.begin(), v1.size(), ptr_gen(cxxrand));
#else
  generate_n(v1.begin(), v1.size(), ptr_gen(rand));
#endif

  for(int i = 0; i < 10; i++)
    cout << v1[i] << ' ';
  cout << endl;
#endif	//	__STL_MEMBER_POINTER_PARAM_BUG	//*TY 07/18/98 - added

  return 0;
}
