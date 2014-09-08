#ifndef SINGLE
//  An adapted ObjectSpace example for use with SGI STL

#include <iostream.h>
#include <map.h>

#ifdef MAIN 
#define map1_test main
#endif
#endif

#include "map1.hpp"
ostream& operator<<(ostream& s, Int x)
  { return s << x.val; }

int map1_test(int, char**)
{
  cout<<"Results of map1_test:"<<endl;
  typedef map<char, Int, less<char> > maptype;
  maptype m;
  // Store mappings between roman numerals and decimals.
  m['l'] = 50;
  m['x'] = 20; // Deliberate mistake.
  m['v'] = 5;
  m['i'] = 1;
  cout << "m['x'] = " << m['x'] << endl;
  m['x'] = 10; // Correct mistake.
  cout << "m['x'] = " << m['x'] << endl;
  cout << "m['z'] = " << m['z'] << endl; // Note default value is added.
  cout << "m.count('z') = " << m.count('z') << endl;
  pair<maptype::iterator, bool> p =
      m.insert(pair<const char, Int>('c', 100));
  if(p.second)
    cout << "First insertion successful" << endl;
  p = m.insert(pair<const char, Int>('c', 100));
  if(p.second)
    cout << "Second insertion successful" << endl;
  else
    cout << "Existing pair " <<(*(p.first)).first
         << " -> " <<(*(p.first)).second << endl;
  return 0;
}
