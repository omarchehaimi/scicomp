#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include "matrix.h"
#include <iostream>
#include <string>

template <typename T>
Matrix<T>::Matrix(unsigned _width, unsigned _height, const T& init)
    :width(_width), height(_height) {
    mat = new double[width*height];
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            mat[height*i + j] = init;
        }
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& copied) {

    if (&copied == this)
        return *this;
    
    unsigned new_width = copied.get_width();
    unsigned new_height = copied.get_height();

    for (int i=0; i<new_width; i++) {
        for (int j=0; j<new_height; j++) {
            mat[i*height + j] = copied(i, j);
        }
    }

    width = new_width;
    height = new_height;

    return *this;
}

template <typename T>
void Matrix<T>::set_val(const unsigned& i, const unsigned& j, const T& val) {
    Matrix<T>::check_size(i, width, "i");
    Matrix<T>::check_size(j, height, "j");
    mat[height*i + j] = val;
}

template <typename T>
void Matrix<T>::check_size(const unsigned& index, const unsigned& dimension, 
    const std::string& index_name) const {
    if (index>=dimension) {
        std::string message = "\nThe index " + index_name + "=" + 
            std::to_string(index) + " is out of bound for a matrix of (" + 
            std::to_string(width) + ", " 
            + std::to_string(height) + ").\n";
        throw std::invalid_argument(message);
    }
}

template <typename T>
T& Matrix<T>::operator()(const unsigned& i, const unsigned& j) const {
    Matrix<T>::check_size(i, width, "i");
    Matrix<T>::check_size(j, height, "j");
    return mat[height*i + j];
}

template <typename T> 
void Matrix<T>::print_matrix() {
    for (int i=0; i<width; i++) {
        for (int j=0; j<height; j++) {
            std::cout << mat[height*i + j] << " ";
        }
        std::cout << "\n";
    }
}

template <typename T>
unsigned Matrix<T>::get_width() const {
    return width;
}

template <typename T>
unsigned Matrix<T>::get_height() const {
    return height;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete [] mat;
}

#endif