#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <bvector.h>

#ifdef MAIN 
#define bvec1_test main
#endif
#endif

int bvec1_test(int, char**)
{
  bool ii[3]= {1,0,1};
  cout<<"Results of bvec1_test:"<<endl;
  bit_vector b(3);
  int i;
  for(i = 0; i < b.size(); i++)
    cout << 
#if defined(__MRC__) || defined(__SC__)	//*TY 01/05/1999 - 
	(bool)				//*TY 01/05/1999 - added bool() since MrCpp forgets to apply user defined conversion operator
#endif					//*TY 01/05/1999 - 
	b[i];
  cout << endl;
  b[0] = b[2] = 1;
  for(i = 0; i < b.size(); i++)
    cout << 
#if defined(__MRC__) || defined(__SC__)	//*TY 01/05/1999 - 
	(bool)				//*TY 01/05/1999 - added bool() since MrCpp forgets to apply user defined conversion operator
#endif					//*TY 01/05/1999 - 
	b[i];
  cout << endl;
  b.insert(b.begin(),(bool*)ii, ii+2);
  for(i = 0; i < b.size(); i++)
    cout << 
#if defined(__MRC__) || defined(__SC__)	//*TY 01/05/1999 - 
	(bool)				//*TY 01/05/1999 - added bool() since MrCpp forgets to apply user defined conversion operator
#endif					//*TY 01/05/1999 - 
	b[i];
  cout << endl;
  return 0;
}
