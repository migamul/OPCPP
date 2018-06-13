#include <cstddef>
#include <cassert>
#include <array>
#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <fstream>
#include <stdexcept>

using namespace std;

// Dio implementacije operacija -- nadopuniti

// Deklaracija - OK
 class Scalar; 

// Klasa obilježja koja nam omogućava da vektor tretiramo kroz 
// reference, a skalare po vrijednosti. - OK
template <typename T>
struct Traits
{
   typedef T const& ExprRef;
};
// Specijalizacija na skalare
// Na skalare ne uzimamo referencu jer im vijek trajanja može biti kraći od 
// vijeka trajanja izraza koji se izračunava. - OK
template <>
struct Traits<Scalar>
{
   typedef Scalar ExprRef;
};


// Klasa koja reprezentira zbrajanje. - OK
template <typename OP1, typename OP2>
class Add
{
    private:
        typename Traits<OP1>::ExprRef op1;
        typename Traits<OP2>::ExprRef op2;
    public:
        Add(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
        double operator[](int i) const
        {
            return op1[i]+op2[i];
        }
        friend ostream& operator<<(ostream& out, Add const& vec)
        {
            out<<"Add<"<<vec.op1<<", "<<vec.op2<<">";
            return out;
        }

};

//Klasa koja reprezentira oduzimanje. - OK
template <typename OP1, typename OP2>
class Sub
{
    private:
        typename Traits<OP1>::ExprRef op1;
        typename Traits<OP2>::ExprRef op2;
    public:
        Sub(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
        double operator[](int i) const
        {
            return op1[i]-op2[i];
        }
        friend std::ostream& operator<< (std::ostream& out, const Sub& vec)
        {
            out << "Sub<" << vec.op1 <<"," << vec.op2 << ">";
            return out;
        }
};

//Klasa koja reprezentira množenje. -OK
template <typename OP1, typename OP2>
class Mult
{
    private:
        typename Traits<OP1>::ExprRef op1;
        typename Traits<OP2>::ExprRef op2;
    public:
        Mult(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
        double operator[](int i) const
        {
            return op1[i]*op2[i];
        }
        friend ostream& operator<<(ostream& out, Mult const& vec)
        {
            out<<"Mult<"<<vec.op1<<","<<vec.op2<<">";
            return out;
        }
};

// Operator indeksiranja vraća vrijednost skalara. - OK
class Scalar
{
    private:
        double val;
        //double const &val;
    public:
    	Scalar(double const& v) : val(v) {}
        double operator[](size_t) const
        {
            return val;
        }
        friend std::ostream& operator<< (std::ostream& out, const Scalar& sca)
        {
            out << sca.val; return out;
        }
};

// - OK
template <size_t N, typename Rep = std::array<double,N> >
class Vector
{
    private:
        Rep expr_rep;  // vektor ili reprezentacija operacije nad vektorima
    public:
        // Polje iz skalarne vrijednosti
        explicit Vector(double val = 0.0) {expr_rep.fill(val);}
        // Polje iz reprezentacije
        Vector(Rep const& r) : expr_rep(r) {}
        // pridruživanje polja različitog tipa
        template <typename Rep2>
        Vector& operator=(Vector<N,Rep2> const& rhs)
        {
            for(size_t i=0; i < N; ++i) expr_rep[i]= rhs[i];
            return *this;
        }
        size_t size() const { return N; }

        double  operator[](size_t i) const {  return expr_rep[i]; }
        double& operator[](size_t i) { return expr_rep[i]; }

        Rep const& rep() const { return expr_rep; }
        Rep&       rep()       { return expr_rep; }

        friend std::ostream& operator<<(std::ostream& out, const Vector& vec)
        {
            out << vec.expr_rep;
            return out;
        }
};

// Ispis - OK
template<size_t N>
ostream& operator<<(ostream& out, std::array<double, N>)
{
    out << N;
    return out;
}

// Operator zbrajanje vektora - OK
template <size_t N,   typename R1, typename R2>
Vector<N, Add<R1,R2> >
operator+(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Add<R1,R2> >( Add<R1,R2>( a.rep(),b.rep() ) );
}

// Operator oduzimanja vektora. - OK
template <size_t N,   typename R1, typename R2>
Vector<N, Sub<R1,R2> >
operator-(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Sub<R1,R2> >( Sub<R1,R2>( a.rep(),b.rep() ) );
}

// Operator množenja vektora. - OK
template <size_t N,   typename R1, typename R2>
Vector<N, Mult<R1,R2> >
operator*(Vector<N,R1> const& a, Vector<N,R2> const& b)
{
    return Vector<N, Mult<R1,R2> >( Mult<R1,R2>( a.rep(),b.rep() ) );
}

// Operator zbrajanja skalara i vektora. - OK
template <size_t N, typename R1>
Vector <N, Add<R1,Scalar> >
operator+(Vector <N, R1> const& a, double const& n)
{
    return Vector<N, Add<R1, Scalar> >(Add<R1, Scalar> (a.rep(), Scalar(n)));
}

template <size_t N,   typename R1>
Vector<N, Add<Scalar,R1> >
operator+(double const& v, Vector<N,R1> const& b)
{
    return Vector<N, Add<Scalar, R1> >( Add<Scalar, R1>( Scalar(v),b.rep() ) );
}


// Operator množenje skalar * vektor. - OK
template <size_t N, typename R2>
Vector<N, Mult<Scalar,R2> >
operator*(double const& a, Vector<N,R2> const& b)
{
    return Vector<N,Mult<Scalar,R2> >( Mult<Scalar,R2>( Scalar(a), b.rep() ) );
}

template <size_t N, typename R1>
Vector <N, Mult<R1,Scalar> >
operator*(Vector <N, R1> const& a, double const& b)
{
    return Vector<N, Mult<R1, Scalar> >(Mult <R1, Scalar> (a.rep(), Scalar(b)));
}

// Operator oduzimanja sklara i vektora. - OK
template <size_t N, typename R1>
Vector <N, Sub<R1,Scalar> >
operator-(Vector <N, R1> const& a, double const& n)
{
    return Vector<N, Sub<R1, Scalar> >(Sub<R1, Scalar> (a.rep(), Scalar(n)));
}

template <size_t N,   typename R1>
Vector<N, Sub<Scalar,R1> >
operator-(double const& v, Vector<N,R1> const& b)
{
    return Vector<N, Sub<Scalar, R1> >( Sub<Scalar, R1>( Scalar(v),b.rep() ) );
}

//---------------------------------------------------------------------------------------------------------------------------------------------

template <typename T, size_t N, size_t M>
class Array2D
{
private:
    T m_data[N][M];
public:

    const T& operator()(size_t i, size_t j) const
    {
        return m_data[i][j];
    }
    T& operator()(size_t i, size_t j)
    {
        return m_data[i][j];
    }

    //kontrola kopiranja

    size_t rows()const
    {
        return N;
    }
    size_t cols()const
    {
        return M;
    }
};

template <size_t N, size_t M>
class Matrix: public Array2D<double,N,M>
{
    public:
        explicit Matrix(double val=0.0)
        {
            for(auto i = 0; i < this->rows(); i++)
                for(auto j = 0; j < this->cols(); j++)
                    this->operator()(i,j) = val;
        }
        // matrica iz reprezentacije
        Matrix(double const polje[N][M])
        {
            for(auto i = 0; i < N; i++)
                for(auto j = 0; j < M; j++)
                     this->operator ()(i,j)=polje[i][j];
        }

        template <typename T>
        Matrix& operator=(Matrix<N,M> const& A)
        {
            for(size_t i = 0; i < N; ++i)
                for(size_t j = 0; j < M; j++)
                    this->operator ()(i,j)=A[i][j];
            return *this;
        }
};

template <typename OP1, typename OP2>
class Mult1
{
    private:
        OP1 const& op1;
        typename Traits<OP2>::ExprRef op2;
    public:
        Mult1(OP1 const& a, OP2 const& b) : op1(a), op2(b) {}
        double operator[](int i) const
        {
            double rez = 0.0;
            for(size_t j = 0; j < op1.cols(); j++)
                rez+=op1(i,j)*op2[j];
            return rez;
        }
};

template <size_t N, size_t M,typename R2>
Vector<N, Mult1<Matrix<N,M> ,R2> >
operator*(Matrix<N,M> const& a, Vector<M,R2> const& b)
{
    return Vector<N, Mult1<Matrix<N,M>, R2> >( Mult1< Matrix<N,M> ,R2 >( a, b.rep() ) );
}

template<size_t N, size_t M>
void makeTridiagonalMatrix(Matrix<N,M> &A, double x, double y)
{
    for(size_t i = 0; i < N; i++)
        A(i,i) = x;
    for(size_t i = 0; i < N; i++)
    {
        if(i<(N-1))
            A(i,i+1) = y;
        if(i>0)
            A(i,i-1) = y;
    }
}
