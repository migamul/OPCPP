#include "zadatak.h"
// Ubaciti potrebne include datoteke
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>
//#include <set>

using namespace std;

template <typename T>
void print(T const &t)
{
    for(auto const &x:t)
        cout << x << " ";
    cout << endl;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------
// Zadan je raspon iteratora unutar stringa. Pročitati i vratiti prvu riječ iz stringa.
// Postaviti iterator it na prvu interpunkciju/bjelinu iza pročitane riječi ili na itend
// (end-iterator) ako takve nema.
// Riječi su cjeline međusobno odvojene bjelinama i/ili interpunkcijama: ,.!?:;()
// Bjeline su  \n\t\v.

std::string procitaj_rijec(std::string::const_iterator & it, std::string::const_iterator itend)
{
  // implementacija

    string rijec;

    while(*it == ',' || *it == '.' || *it == '!' || *it == '?' || *it == ':' || *it == ';' || *it == '(' || *it == ')' || *it == '\n' || *it == '\t' || *it == '\v' || *it == ' ' || *it == '"' || *it == '\0')
    {
        if(it == itend)
            break;
        ++it;
    }

    while(*it != ',' && *it != '.' && *it != '!' && *it != '?' && *it != ':' && *it != ';' && *it != '(' && *it != ')' && *it != '\n' && *it != '\t' && *it != '\v' && *it != ' ' &&  *it != '"' && *it != '\0')
    {

        rijec+=*it;
        if(it == itend)
            break;
        ++it;
    }

    return rijec;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Otvoriti datoteku file_name za čitanje, učitati tekst (npr. liniju po liniju)
// i smjestiti riječi u mapu. Riječ je ključ, a vrijednost je broj pnavljanja riječi.
// Riječ se učitava pomoću rutine ucitaj_rijec.

void procitaj_datoteku(std::string file_name, std::map<std::string,int> & word_list)
{
  // implementacija

    const string in(file_name);
    ifstream infile;
    infile.open(in.c_str());

    if(!infile)
        throw runtime_error("Ne moze se otvoriti ulazna datoteka");

    string line;
    vector<string> vec;
    while(getline(infile,line))
    {
        string::const_iterator be = line.begin();
        string::const_iterator en = line.end()-1;
        while(be <= en)
        {
            string rijec = procitaj_rijec(be,en);
            if(rijec.empty())
                break;

            if(be == en || be > en)
            {
                vec.push_back(rijec);
                break;
            }
            vec.push_back(rijec);
            if(line.empty())
                vec.pop_back();
        }
    }
    //print(vec);

    vector <string>::iterator vi = vec.begin();

    for( ; vi != vec.end(); ++vi)
    {
        ++word_list[*vi];
    }

    map <string,int>::iterator mi = word_list.begin();

    //kontrola ispisa
    /* for( ; mi != word_list.end(); ++mi)
    {
        cout << mi->first << ":" << mi->second << endl;
    } */

    infile.close();
}

///------------------------------------------------------------------------------------------------------------------------------------------------
// Vrati listu riječi koje se najčešće pojavljuju u mapi (std::list) i broj ponavljanja (int).

std::pair<std::list<std::string>, int> naj(std::map<std::string,int> const & word_list)
{
  // implementacija

    map <string,int>::const_iterator mi = word_list.begin();

    list< string> l;
    int best = 0;

    for( ; mi != word_list.end(); ++mi)
    {
        if(mi->second > best)
            best = mi->second;
    }

    map <string,int>::const_iterator mii = word_list.begin();

    for( ; mii != word_list.end(); ++mii)
    {
        if(mii->second == best)
        {
            l.push_back(mii->first);
        }
    }

    pair < list<string>, int > najbolji;

    najbolji.first = l;
    najbolji.second = best;

    return najbolji;
}

///----------------------------------------------------------------------------------------------------------------------------------------------------
// Argument grupe sadrži grupe riječi (ključ je ime grupe, a vrijednosti
// su riječi koje pripadaju grupi).
// Funkcija treba za svaku grupu riječi sumirati broj pojavljivanja svih riječi
// iz grupe u tekstu te vratiti vrijednosti u vektoru. Na i-tom mjestu u povratnom vektoru
// je broj pojavljivanja riječi iz i-te grupe (prema uređaju u multimap varijabli).
// Argument word_list je std::map svih riječi s brojem njihovih pojavljivanja.

std::vector<int>
broj_iz_grupe(std::map<std::string,int> const & word_list,
              std::multimap<std::string, std::string> const & grupe)
{
    // implementacija

    vector <int> vec;

    multimap <string,string>::const_iterator mmi = grupe.begin();
    multimap <string,string>::const_iterator it = grupe.begin();
    map <string,int>::const_iterator mi = word_list.begin();

    int sum = 0;
    for(multimap <string,string>::const_iterator it = grupe.begin() ; mmi != grupe.end(); ++mmi)
    {
        it = mmi;
        for(map <string,int>::const_iterator mi = word_list.begin() ; mi != word_list.end(); ++mi)
        {
                if(mmi->second == mi->first)
                {
                    sum = sum + mi->second;
                }
        }
        if(mmi->first != (++it)->first)
        {
            vec.push_back(sum);
            sum = 0;
        }
    }
    //print(vec);

    return vec;
}
