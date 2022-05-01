#ifndef __MATRIX_H
#define __MATRIX_H

#include <string>

/**
 * @brief Simple class to handle basic matrix operations. 
 * For storing the matrix I used a 1D array as an exercise on the representation 
 * of a 2D array in 1D.
 * 
 * @tparam T 
 */

template <typename T> 
class Matrix {
    private:
        unsigned width, height;
        T* mat;
        void check_size(const unsigned& index, const unsigned& dimension, 
                        const std::string& index_name) const;
    public:
        Matrix(unsigned _width, unsigned _height, const T& init);
        virtual ~Matrix();
        Matrix<T>& operator=(const Matrix<T>& copied);
        void print_matrix();
        T& operator()(const unsigned& i, const unsigned& j) const;
        void set_val(const unsigned& i, const unsigned& j, const T& val);
        unsigned get_width() const;
        unsigned get_height() const;
};

#include "matrix.cpp"

#endif