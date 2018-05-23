#ifndef _ISORT_H_ 
#define _ISORT_H_ 
#include <vector>
#include <algorithm>
#include <list>

// Verzija s indeksima
template <typename Record>
void insertion_sort_ind(std::vector<Record> & vec)
{
    int i,j;
    int n = vec.size();
    for(i = 1; i < n; i++)
    {
        Record k = vec[i];
        j = i-1;

        while( j >= 0 && vec[j] > k)
        {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = k;
    }
}


// Verzija koja uzima iterator range -- koristiti samo std::next i std::prev
template <typename Iter>
void insertion_sort(Iter first, Iter last)
{
    if(first == last)
        return;

    auto&& it = std::next(first); //auto=prepoznaje tip
    //Iter it = std::next(first);
    for(; it != last; ++it)
    {
        auto k = *it;
        auto it1 = it;

        while( it1 != first && *std::prev(it1) > k )
        {
            *it1 = *std::prev(it1);
            --it1;
        }

        *it1 = k;
    }
}


// verzija sa algoritmima std::rotate i std::upper_bound
template <typename Iter>
void insertion_sort1(Iter first, Iter last)
{
   if(first == last)
       return;

   Iter it;
   for(it = first; it != last; ++it)
   {
       std::rotate( std::upper_bound(first, it, *it), it, std::next(it));
   }
}


#endif
