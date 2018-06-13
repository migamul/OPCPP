#include <iostream>
#include "zadatak.h"

using namespace std;

template <typename T>
void print(T const &t)
{
    for(auto const &x:t)
        cout << x << " ";
    cout << endl;
}

int main()
{
    // Ovdje napisati svoje vlastite testove!

    ///test za procitaj_rijec

    /* std::string str (" ,:Test ;string         "
                     "kjbfvk    sljbsgl.   bla");
    string::const_iterator beg = str.begin();
    string::const_iterator ben = str.end()-1;
    vector <string> vec;
    while(beg <= ben)
    {
        string rijec = procitaj_rijec(beg,ben);
        if( beg > ben || beg == ben)
        {
            vec.push_back(rijec);
            break;
        }
        vec.push_back(rijec);
    }
    print(vec); */


    ///test za procitaj_datoteku

    /* map <string,int> m;
    procitaj_datoteku("../../src/text.txt",m); */


    ///test za naj

    /* pair < list<string>, int > najbolji;
    najbolji = naj(m);

    cout << *najbolji.first.begin() << " " << najbolji.second << endl; */

    ///test za broj_iz_grupe

    /* map <string,int> m;
    multimap<std::string, std::string> grupe;
    grupe.insert(std::make_pair("Grupa1", "the"));
    grupe.insert(std::make_pair("Grupa1", "a"));

    grupe.insert(std::make_pair("Grupa2", "is"));
    grupe.insert(std::make_pair("Grupa2", "are"));

    //procitaj_datoteku("../src/text.txt", m);

    vector<int> vec;
    vec = broj_iz_grupe(m, grupe);

    cout << vec.size() << endl;
    cout << vec[0] << " " << vec[1]; */

    return 0;
}
