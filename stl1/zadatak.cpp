#include "zadatak.h"

// Ubaciti potrebne include datoteke
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <list>
#include <iomanip>

using namespace std;

//pomocna funkcija za kontolu ispisa
template <typename T>
void print(T const &t)
{
    for(auto const &x:t)
        cout << x << " ";
    cout << endl;
}

std::vector<int> zadatak1(std::string const & file_name)
{
  // Implementacija zadatka 1

    string in(file_name);
    ifstream infile;
    infile.open(in.c_str());

    if(!infile)
       throw runtime_error("Ne moze se otvoriti ulazna datoteka");

    istream_iterator<int> isi(infile);
    istream_iterator<int> isi_end;
    vector<int> vec (isi, isi_end);

    //u zadatku kaze zamjena algoritmom iz std; nemem ovako
    /* for(auto& x :vec)
        if(x==0)
           x=9; */

    int staro = 0;
    int novo = 9;
    replace(vec.begin(), vec.end(), staro, novo);

    infile.close();
    return vec;
}

void zadatak2(std::string const & file_name)
{
  // Implementacija zadatka 2

    string in(file_name);
    ifstream infile;
    infile.open(in.c_str());

    if(!infile)
       throw runtime_error("Ne moze se otvoriti ulazna datoteka");

    istream_iterator<float> isi(infile);
    istream_iterator<float> isi_end;
    vector<float> vec;

    copy(isi, isi_end, back_inserter(vec));

    ofstream outfile;
    outfile.open("3cols.txt");
    outfile.clear();

    if(!outfile)
        throw runtime_error("Ne moze se otvoriti izlazna datoteka");

    //print(vec);

    vector<float> pom;
    for(unsigned int i=0; i<vec.size(); i++)
    {
        pom.push_back(vec[i]);
        pom.push_back(sin(vec[i]));
        pom.push_back(exp(vec[i]));
    }

    //print (pom);

    //upis u datoteku 3cols.txt
    for(unsigned int i=0; i<pom.size(); i++)
    {
        outfile << right << showpos << setw(13) << scientific << pom[i];
        if(i%3 != 2)
            outfile << " ";
        if(i%3 == 2)
            outfile << endl;
    }

    infile.close();
    outfile.close();
}

std::list<int> zadatak3()
{
  // Implementacija zadatka 3

    list<int> list1{1,2,3,4,5,6,7,8,9};
    list<int> list2{1,2,3,4,5,6,7,8,9};

    while(*list1.begin() != 5)
        next_permutation(list1.begin(), list1.end());

    while(*list2.begin() != 9)
        next_permutation(list2.begin(), list2.end());

    list<int>::iterator l1,l2b,l2e;

    l1=find(list1.begin(), list1.end(), 3);
    assert(*l1 == 3);

    //provjera je li prvo 4 pa 7 ili 7 pa 4
    int four=0, seven=0;
    for(auto& x :list2)
     {
         if(x == 4)
         {
            four = 1;
            break;
         }
         if(x == 7)
         {
             seven = 1;
             break;
         }
    }

    if(four == 1)
    {
        l2b=find(list2.begin(), list2.end(), 4);
        assert(*l2b == 4);
        l2e=find(list2.begin(), list2.end(), 7);
        assert(*l2e == 7);
        //l2b++;  //dakle,on se ne pomakne za mjesto(prije nije gledao i 4,sad gleda)

        //kontrola ispisa
        /* print(list1);
        cout << endl;
        print(list2);
        cout << endl; */

        list1.splice(l1, list2, l2b, l2e);

        //kontrola ispisa
        /* print(list1);
        cout << endl;
        print(list2); */
    }

    if(seven == 1)
    {
        l2b=find(list2.begin(), list2.end(), 7);
        assert(*l2b == 7);
        l2e=find(list2.begin(), list2.end(), 4);
        assert(*l2e == 4);
        //l2b++;

        //kontrola ispisa
        /* print(list1);
        cout << endl;
        print(list2);
        cout << endl; */

        list1.splice(l1, list2, l2b, l2e);

        //kontrola ispisa
        /* print(list1);
        cout << endl;
        print(list2); */
    }

    return list1;
}
