#include "lista.h"
#include <iostream>

int main()
{
// Ovdje pišete vlastite testove klase. 

 List<int> l;

 l.push_back(25);
 l.push_back(1100);
 l.push_back(300);
 //l.push_back(400);
 //cout << l.size() << endl;

 //l.remove(0);
 //cout << l.current();
 //l.insert(0,600);
 //cout << l.current();
 l.sort();
 l.setPosition(1);
 cout << l.current();

 //l.clear();

 //cout << l.size() << endl;
   
  return 0;
}
 

