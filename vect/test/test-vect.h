#ifndef TEST_LISTA_H
#define TEST_LISTA_H

#include "gtest/gtest.h"
#include <cstddef>
#include "../src/vect.h"


template <typename T>
class VectTest  : public ::testing::Test {
public:
     //Vect<T> vec;
     T * get_mdata(Vect<T> const & vec) { return vec.mdata;       }
     T * get_mff  (Vect<T> const & vec) { return vec.mfirst_free; }
     T * get_mend (Vect<T> const & vec) { return vec.mend;        }
};

#endif
