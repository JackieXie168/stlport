#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <algo.h>

#ifdef MAIN 
#define istmit1_test main
#endif
#endif
int istmit1_test(int, char**)
{
  cout<<"Results of istmit1_test:"<<endl;
  char buffer [100];
  int i = 0;
  cin.unsetf(ios::skipws); // Disable white-space skipping.
  cout << "Please enter a string: ";
#ifndef __STL_LIMITED_DEFAULT_TEMPLATES
  istream_iterator<char> s(cin),eos;		//*TY 01/10/1999 - added eos()
#else
  istream_iterator<char, ptrdiff_t> s(cin),eos;		//*TY 01/10/1999 - added eos()
#endif
  while(!(s == eos)  &&		
	//*TY 01/10/1999 - added end of stream check 
	// NOTE operator!= should not be used here ifndef __STL_FUNCTION_TMPL_PARTIAL_ORDER
  		*s != '\n' &&
  		(i < sizeof(buffer)/sizeof(buffer[0])) )		//*TY 07/28/98 - added index check
    buffer[i++] = *s++;
  buffer[i] = '\0'; // Null terminate buffer.
  cout << "read " << buffer << endl;
  return 0;
}
