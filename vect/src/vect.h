#ifndef _VECT_H_IS_INCLUDED_
#define _VECT_H_IS_INCLUDED_

#include <iostream>
#include <string>

// deklaracija potrebna za testiranje
template <typename> class VectTest;

template <typename T>
class Vect
{
    friend class VectTest<T>;  // da testovi mogu dohvatiti privatne varijable
public:
    //explicit Vect(size_t n = 0, T v= {});  // Ctor
    Vect();
    Vect(size_t n);
    Vect(size_t n, T v);

    // Kontrola kopiranja dolazi ovdje
    // CCtor
    Vect(const Vect<T>& v);
    // MCtor
    Vect(Vect<T> && v) noexcept;
    // OP
    Vect& operator=(const Vect<T>& v);
    // MOP
    Vect& operator=(Vect<T> && v) noexcept;
    // DTOR
    ~Vect();

    // dohvat elemenata (operator [])
    T& operator[](size_t i);
    const T& operator[](size_t i) const;

    // push_back metoda
    void push_back(T t);

     // info rutine size() i capacity()
    size_t size() const;
    size_t capacity() const;

     // operatori +=, -=, *=
    Vect& operator+=(const Vect<T>& v);
    Vect& operator-=(const Vect<T>& v);
    Vect& operator*=(size_t s);

     // euklidska norma vraća double !
     double two_norm() const;
private:
        T *mdata;       // pokazivač na prvi element
        T *mfirst_free; // pokazivač na prvo slobodno mjesto
        T *mend;        // pokazivač na kraj alociranog prostora
                             // (jedno mjesto iza posljednjeg)

        // Oslobodi zauzeti prostor (pomoću alokatora)
        void free();

        // realociraj na novu lokaciju. Povećaj dimenziju vektora 2 puta; ako je
        // vektor prazan alociraj jedan element.
        void reallocate();

        // dodati vlastite privatne metode.
        bool has_space() const;

        // alokator ne mora imati pristup varijablama članicama klase pa ga činimo
        // statičkim. Ne zaboraviti definirati ga.
        static std::allocator<T> alloc;
};

// Deklaracija operator +, - i <<
template <typename T>
Vect<T>
operator+(Vect<T> const& v1,Vect<T> const& v2);

template <typename T>
Vect<T>
operator-(Vect<T> const& v1,Vect<T> const& v2);

template <typename T>
std::ostream& operator<<(std::ostream& out, Vect<T> v);


// Implementacija je u posebnoj .h datoteci
#include "vect_impl.h"

#endif
