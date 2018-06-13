#include "zadatak.h"
#include "zadatak.cpp"

int main()
{
    std::vector<int> vec = zadatak1("../../src/brojevi.txt");
    zadatak2("../../src/fpbrojevi.txt");
    std::list<int> l = zadatak3();

    //kontrola ispisa
    //print (vec);
    //print (l);

    return 0;
}
