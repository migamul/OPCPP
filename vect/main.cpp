#include <iostream>
#include "vect.h"

using namespace std;

int main()
{
    // Vaši testovi dolaze ovdje.

    Vect<int> vec;
    cout << vec.size() << " " << vec.capacity() << endl;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    cout << vec.size() << " " << vec.capacity() << endl;
    cout << vec << endl;

    Vect<int> v1(5);
    cout << v1.size() << " " << v1.capacity() << endl;
    cout << v1 << endl;

    int n = 10;
    Vect<int> v2(n,3);
    cout << v2.size() << " " << v2.capacity() << endl;
    cout << v2 << endl;

    Vect<int> v3(move(v2));
    cout << v3.size() << " " << v3.capacity() << endl;
    cout << v3 << endl;

    Vect<int> v4 = move(v1);
    cout << v4.size() << " " << v4.capacity() << endl;
    cout << v4 << endl;

    Vect<int> vec1(3,5);
    Vect<int> vec2(3,5);
    vec1+=vec2;
    cout << vec1 << " " << vec2 << endl;

    Vect<int> vec3(3,5);
    Vect<int> vec4(3,5);
    vec3-=vec4;
    cout << vec3 << " " << vec4 << endl;

    Vect<int> v(5,5);
    Vect<int> ve(5,5);
    Vect<int> vee, veee;
    vee = v + ve;
    cout << vee << endl;
    veee = v - ve;
    cout << veee << endl;

    Vect<double> norm(3,1);
    double no = norm.two_norm();
    cout << norm << " " << no << endl;

    return 0;
}
