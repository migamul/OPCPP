// Vaša implementacija dolazi ovdje.

#include <iostream>
#include <memory>
#include <string>
#include <cmath>
#include <utility>

#include "vect.h"

using namespace std;

// Konstruktori -----------------------------------------------------------
template <typename T>
allocator<T> Vect<T>::alloc;

template <typename T>
Vect<T>::Vect()
{
    mdata = nullptr;
    mfirst_free = nullptr;
    mend = nullptr;
}

template <typename T>
Vect<T>::Vect(size_t n)
{
    if(n == 0)
    {
        mdata = nullptr;
        mfirst_free = nullptr;
        mend = nullptr;
    }
    mdata = alloc.allocate(n);
    for(size_t i = 0; i < n; ++i)
       alloc.construct(mdata + i, NULL);
    mfirst_free = mend = mdata + n;
}

template <typename T>
Vect<T>::Vect(size_t n, T val)
{
     if(n == 0)
     {
         mdata = nullptr;
         mfirst_free = nullptr;
         mend = nullptr;
         val = {};
     }
     else
     {
         mdata = alloc.allocate(n);
         for(size_t i=0; i < n; ++i)
            alloc.construct(mdata + i, val);
         mfirst_free = mend = mdata + n;
     }
}

// CCtor ----------------------------------------------------------------
template <typename T>
Vect<T>::Vect(const Vect<T>& v)
{
    mdata = alloc.allocate(v.capacity());   //alociramo novu memoriju
    uninitialized_copy(v.mdata, v.mfirst_free, mdata);  //prekopiramo podatke
    mfirst_free = mdata + v.size();
    mend = mdata + v.capacity();
}

// MCtor ----------------------------------------------------------------
template <typename T>
Vect<T>::Vect(Vect<T> && v) noexcept
{
   mdata = move(v.mdata);
   mend = move(v.mend);
   mfirst_free = move(v.mfirst_free);
  // uninitialized_copy(v.mdata, v.mfirst_free, mdata);
    v.mdata = nullptr;
    v.mend = nullptr;
    v.mfirst_free = nullptr;
}

// OP ------------------------------------------------------------------
template <typename T>
Vect<T>& Vect<T>::operator=(const Vect<T>& v)
{
    if(this->mdata != v.mdata)
    {
        free();  //oslobodimo ono na sto je vektor pokazivao
        mdata = alloc.allocate(v.capacity());   //alociramo memoriju velicine tocno koliko je v
        uninitialized_copy(v.mdata, v.mfirst_free, mdata);   //kopiramo podatke
        mfirst_free = mdata + v.size();
        mend = mdata + v.capacity();
    }
    return *this;
}

// MOP -----------------------------------------------------------------
template <typename T>
Vect<T>& Vect<T>:: operator=(Vect<T> && v) noexcept
{
   if(this != &v)
   {
       mdata = move(v.mdata);
       mend = move(v.mend);
       mfirst_free = move(v.mfirst_free);
     //  uninitialized_copy(v.mdata, v.mfirst_free, mdata);
       v.mdata = nullptr;
       v.mend = nullptr;
       v.mfirst_free = nullptr;
   }
   return *this;
}

// DTOR -------------------------------------------------------------
template <typename T>
Vect<T>::~Vect()
{
    free();
}

// Push_back --------------------------------------------------------------
template <typename T>
bool Vect<T>::has_space() const
{
    return ( size() == capacity() ) ?  false : true;
}

template <typename T>
void Vect<T>::push_back(T t)
{
    if( !has_space() )
        reallocate();
    alloc.construct(mfirst_free++, t);
}

// [ ] --------------------------------------------------------------------
template <typename T>
const T& Vect<T>::operator[](size_t i) const
{
    return mdata[i];
}

template <typename T>
T& Vect<T>::operator[](size_t i)
{
    return mdata[i];
}

// size() i capacity() ---------------------------------------------------
template <typename T>
size_t Vect<T>::size() const
{
    return mfirst_free - mdata;
}

template <typename T>
size_t Vect<T>::capacity() const
{
    return mend - mdata;
}

// free ------------------------------------------------------------------
template <typename T>
void Vect<T>::free()
{
    size_t n = capacity();
    if(n != 0)
    {
        T* t = mdata;
        while(t != mfirst_free)
        {
            alloc.destroy(t);
            t++;
        }
        alloc.deallocate(mdata, n);
    }
    mdata = nullptr;
    mfirst_free = nullptr;
    mend = nullptr;
}

// reallocate -------------------------------------------------------------
template <typename T>
void Vect<T>::reallocate()
{
    if(capacity() == 0)
    {
        mdata = alloc.allocate(1);
        mfirst_free = mdata;
        mend = mdata + 1;
    }
    else
    {
        size_t vel = capacity()*2;
        T* MD;
        MD = alloc.allocate(vel);
        for(unsigned int i = 0; i < size(); i++)
        {
            MD[i] = mdata[i];
        }
        free();
        mdata = MD;
        mfirst_free = MD + vel/2;
        mend = MD + vel;
    }
}

// two_norm ---------------------------------------------------------------
template <typename T>
double Vect<T>::two_norm() const
{
    double rez = 0.0;
    for(size_t i = 0; i < size(); ++i)
        rez = rez + mdata[i]*mdata[i];
    double norm = sqrt(rez);
    return norm;
}

// += , -= , *=
template <typename T>
Vect<T>& Vect<T>::operator+=(const Vect<T>& v)
{
    size_t sv = v.size();
    size_t s = size();
    if( s != sv)
        throw runtime_error("Sizes don't match");
    for(size_t i=0; i < s; ++i)
        mdata[i] += v.mdata[i];
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator-=(const Vect<T>& v)
{
    size_t sv = v.size();
    size_t s = size();
    if(s != sv)
        throw runtime_error("Sizes don't match");
    for(size_t i=0; i < s; ++i)
        mdata[i] -= v.mdata[i];
    return *this;
}

template <typename T>
Vect<T>& Vect<T>::operator*=(size_t s)
{
    for(size_t i=0; i < size(); ++i)
        mdata[i] *= s;
    return *this;
}

// + , - , print
template <typename T>
Vect<T>
operator+(Vect<T> const& v1, Vect<T> const& v2)
{
   if(v1.size() != v2.size())
       throw runtime_error("Zbrajanje 2 vektora razlicite duljine");

   Vect<T> vec;

   for(size_t i = 0; i< v1.size(); ++i)
       vec.push_back(v1[i] + v2[i]);

   return vec;
}

template <typename T>
Vect<T>
operator-(Vect<T> const& v1, Vect<T> const& v2)
{
   if(v1.size() != v2.size())
       throw runtime_error("Oduzimanje 2 vektora razlicite duljine");

   Vect<T> vec;

   for(size_t i = 0; i< v1.size(); ++i)
       vec.push_back(v1[i] - v2[i]);

   return vec;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, Vect<T> v)
{
    out << '[';
    for (size_t i = 0; i < v.size(); i++)
    {
        out << v[i];
        if(i != (v.size() - 1))
            out << ',';
    }
    out << ']';
    return out;
}
