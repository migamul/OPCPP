#ifndef LISTA_H
#define LISTA_H 

#include <cstddef>  // za std::size_t
#include <stdexcept>
#include <cassert>
#include <iostream>

using namespace std;

template <typename> class ListTest;

// Paramtrizirana struktura koja predstavlja čvor u listi.
// Sadrži vrijednost (value) i pokazivače na prethodni i sljedeći
// element u listi.
template <typename T>
struct Node
{
    T value{};
    Node * previous = nullptr;
    Node * next = nullptr;
};

/**
 * Dvostruko povezana lista s elementima indeksiranim cjelobrojnim indeksima.
 * Indeksi elemenata počinju s nulom. Sve metode koje uzimaju indeks provjeravaju
 * da li je unutar granica i u suprotnom izbacuju std::runtime_error.  
 **/
template <typename T>
class List
{
    friend class ListTest<T>;
	public:
		// Konstruktor
        List() :  mSize(0), mPositionIdx(0), mStart(nullptr), mPosition(nullptr) {}

		// Destruktor
        ~List()
        {
            clear();
        }

		// Obriši (dealociraj) sve elemente liste. 
		void clear();

		// Da li je lista prazna?
		bool empty() const;

		// Broj elemenata u listi. 
		std::size_t size() const;

		// Ubaci element "t" na poziciju "i" u listi. Pozicija "i" mora biti važeća 
		// i tada se element ubacuje na to mjesto, a prijašnji "i"-ti element postaje 
		// "i"+1-vi element. Pozicija "i" može biti jednaka size()  i tada se element ubacuje na kraj liste. 
		// Metoda mora ispravno ubacivati i u praznu listu. Metoda pozicionira listu na novom
		// i-tom elementu (pozivom metode setPosition()). 
        // Novi element se alocira dinamički pomoću new operatora.
		void insert(std::size_t i, T const & t);

		// Izbaciti element iz liste i dealocirati ga pomoću delete. Trenutna pozicija
		// nakon izbacivanja pokazuje na prethodni element ako postoji; kada se izabacuje prvi element
		// onda pokazuje na novi prvi element ili lista ostaje prazna. 
		void remove(std::size_t i);

		// Postaviti trenutnu poziciju na i-to mjesto. Dozvoljeni "i" ide od 0 do 
		// size()-1. Inače izbaci izuzetak std::runtime_error.
		void setPosition(std::size_t i) const;

		// Vrati selektirani element. Konstantan verzija.
        T const & current() const;

		// Vrati selektirani element. Nekonstantna verzija.
        T & current();

        // Dodaje element na kraj liste. Listu pozicionira na novom elementu.
		void push_back(T const & t);

        // Sortira listu pomoću operatora <. Implementirati "insertion sort".
        void sort();

	private:
	   std::size_t mSize;
	   mutable std::size_t mPositionIdx;
       Node<T> * mStart;
	   mutable Node<T> * mPosition;

	   // Vrati pokazivač na selektirani node.
       Node<T> * currentNode()
       {
           return mPosition;
       }
};

template <typename T>
bool List<T>::empty() const
{
  // Implementacija

    return size() == 0;
}

template <typename T>
std::size_t List<T>::size() const
{
    return mSize;
}

template <typename T>
T const & List<T>::current() const
{
 // Implementacija
    Node<T> *temp = currentNode();
    return temp->value;
}

template <typename T>
T & List<T>::current()
{
 // Implementacija
    Node<T> *temp = currentNode();
    return temp->value;

}

template <typename T>
void List<T>::setPosition(std::size_t i) const
{
 // Implementacija
    if(i > mSize)
        throw::runtime_error("veće");
    else if(i < 0)
        throw::runtime_error("manje");

    Node<T> *curr = mStart;

    for(unsigned int j = 0; j < i; ++j)
        curr = curr->next;
    mPosition = curr;
    mPositionIdx = i;
}

template <typename T>
void List<T>::insert(std::size_t i, T const & t)
{
 // Implementacija

    if(i > mSize)
        throw::runtime_error("insert:vece");
    if(i < 0)
        throw::runtime_error("insert:manje");

    if(mStart == nullptr)
    {
        Node<T> *temp = new Node<T>;
        temp->next = nullptr;
        temp->previous = nullptr;
        temp->value = t;
        mStart = temp;
        ++mSize;
        setPosition(0);
        mPosition = temp;
        return ;
    } 
    Node<T> *temp = new Node<T>;
    temp->value = t;
    //temp->next = nullptr;
   // temp->previous = nullptr;

    Node<T> *tail = mStart;
    while(tail->next != nullptr)
        tail = tail->next;

    if(i == 0)
    {
        temp->previous = nullptr;
        temp->next = mStart;
        mStart->previous = temp;
        mStart = temp;
        mPosition = temp;
        ++mSize;
        setPosition(i);
        return ;
    }
    if(i == mSize)
    {
        tail->next = temp;
        temp->previous = tail;
        tail = temp;
        ++mSize;
        mPosition = temp;
        setPosition(i);
        temp->next = nullptr;
        return ;
    }

    Node<T> *curr = mStart;

    for(unsigned int j = 0; j < i-1; ++j)
    {
        curr = curr->next;
    }

    if(curr->next == nullptr)
    {
        curr->next = temp;
        temp->next = nullptr;
        temp->previous = curr;
        ++mSize;
        setPosition(i);
        mPosition = temp;
        return ;
    }
    else
    {
        temp->next = curr->next;
        temp->next->previous = temp;
        curr->next = temp;
        temp->previous = curr;
        ++mSize;
        setPosition(i);
        mPosition = temp;
        return ;
    }
    return ;
}

template <typename T>
void List<T>::remove(std::size_t i)
{
 // Implementacija

    if(i >= mSize)
        throw::runtime_error("vece");
    if(i < 0)
        throw::runtime_error("manje");

    Node<T> *curr = mStart;
    Node<T> *temp = mStart;
    size_t pos = 0;

    Node<T> *tail = mStart;
    while(tail->next != nullptr)
        tail = tail->next;

    while(curr)
    {
        if(pos == i)
        {
            if(mStart == tail)
            {
                mStart = nullptr;
                --mSize;
                mPosition = nullptr;
                setPosition(0);
                //mPositionIdx = 0;
                delete curr;
                return ;
            }
            else if(curr == mStart)
            {
                mStart = curr->next;
                mStart->previous = nullptr;
                --mSize;
                //mPosition = mStart;
                setPosition(0);
                //mPositionIdx = 0;
                delete curr;
                return ;
            }
            else if(i == (mSize-1))
            {
                temp->next = nullptr;
                tail = temp;
                --mSize;
                setPosition(mSize-1);
                mPosition = tail;
                //mPositionIdx = mSize-1;
                delete curr;
                return ;
            }
            else
            {
                temp->next = curr->next;
                curr->next->previous = temp;
                --mSize;
                mPosition = temp;
                mPositionIdx = i-1;
                delete curr;
                return ;
            }
        }
        temp = curr;
        curr = curr->next;
        ++pos;
    }
}


template <typename T>
void List<T>::clear()
{
 // Implementacija

    Node<T> *curr = mStart;
    Node<T> *temp = mStart;

    while( curr )
    {
        curr = curr->next;
        delete temp;
        temp = curr;
    }
    delete temp;
    mStart = nullptr;
    //mPosition = nullptr;
    //mPositionIdx = 0;
    setPosition(0);
    mSize = 0;
}

template <typename T>
void List<T>::push_back(T const & t)
{
 // Implementacija

    if(mStart == nullptr)
    {
        Node<T> *temp = new Node<T>;
        temp->next = nullptr;
        temp->previous = nullptr;
        temp->value = t;
        mStart = temp;
        ++mSize;
       // mPositionIdx = 0;
        setPosition(0);
        //mPosition = mStart;
        return ;
    }
    else
    {
        Node<T> *temp = new Node<T>;
        Node<T> *curr = mStart;

        for(unsigned int j=0; j < mSize - 1 ; ++j)
            curr = curr->next;

        curr->next = temp;
        temp->next = nullptr;
        temp->previous = curr;
        temp->value = t;
        ++mSize;
        setPosition(mSize-1);
        //mPositionIdx = mSize - 1;
        //mPosition = temp;
        return ;
    }
}

template <typename T>
void List<T>::sort()
{
 // Implementacija

    Node<T> *temp, *curr;

    for(temp = mStart->next; temp != nullptr; temp = temp->next)
    {
        size_t t = temp->value;
        curr = temp;

        while(curr->previous != nullptr && curr->previous->value >= t)
        {
            curr->value = curr->previous->value;
            curr = curr->previous;
        }
        curr->value = t;
    }
}

#endif /* LISTA_H */
