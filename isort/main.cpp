#include "isort.h"
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <iterator>

int main()
{
    // Testirajte vaše algoritme na vektoru i listi.

    ///vektori:
    std::vector<int> vec = {1,6,4,9,3,0,-2};
    //std::vector<std::string> vec = {"bla","blaa","b","bl","blaaa"};

    ///liste:
    //std::list<int> li = {15,25,-8,0,-6,9,8,9};

    ///sort za vektore:
    insertion_sort_ind(vec);
    //insertion_sort(vec.begin(), vec.end());
    //insertion_sort1(vec.begin(), vec.end());
    //insertion_sort1(li.begin(),li.end());

    ///sort za liste:
    //insertion_sort(li.begin(),li.end());
    //insertion_sort1(li.begin(),li.end());

    ///ispis za vektore:
    for(unsigned int i=0; i<vec.size(); i++)
       std::cout << vec[i] << " ";

    ///ispis za liste:
    /* std::list<int>::iterator it;

    for(it = li.begin(); it != li.end(); it++)
       std::cout << *it << " ";
       */

    return 0;
}
