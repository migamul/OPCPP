#include <iostream>
#include <ctime>
#include <chrono>
#include "operations.h"

using namespace std;

void test(bool t)
{
    if(t) cout << "OK\n";
    else  cout << "GRESKA\n";
}


// Main s predavanja
int main()
{
    // Vaši testovi i test brzine

    const size_t max = 3;

    Vector<max>  x, y(2.0), z;
    x[0]=1.0; x[1]= 1.5; x[2]=1;

    z = x + y;
    test(z[2] == x[2]+y[2]);
    z = 2.0*x + y;
    test(z[1] == 2*x[1]+y[1]);
    z = x*2.0 + y;
    test(z[0] == 2*x[0]+y[0]);
    z = 4.0*(x*2.0 + y);
    test(z[1] == 8*x[1]+4*y[1]);
    z = 1.0 + (1.2*x + y*2.0)*4.0 - x + 2.0;
    test(z[2] == 3+4*(1.2*x[2]+2*y[2]) -x[2]);
    z[1] = 2.0;
    z = z*z;
    test(z[1]==4.0);

    cout << " x+ y      = " << x+y << endl;
    cout << " 2*x+ y    = " << 2.0*x+y << endl;
    cout << " x*2+y     = " << x*2.0 + y << endl;
    cout << " 4*(x*2+y) = " << 4.0*(x*2.0 + y) << endl;
    cout << " 1 + (1.2 * x + y * 2.0)*4.0 - x + 2 = "
         << 1.0 + (1.2*x + y*2.0)*4.0 - x + 2.0 << endl;

	return 0;
}
