//
// Created by Spark on 20/02/2019.
//

#include "complex.hpp"

//! A constructor.
/*!
  A more elaborate description of the constructor.
*/
Complex::Complex(double _real, double _imaginary) {
    this->real = _real;
    this->imaginary = _imaginary;
}

//! A copy constructor.
/*!
  A more elaborate description of the copy constructor.
*/
Complex::Complex(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;
}

//! A destructor.
/*!
  A more elaborate description of the destructor.
*/
Complex::~Complex() {

}

Complex& Complex::operator=(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;

    return *this;
}

double Complex::getReal() const {
    return this->real;
}

double Complex::getImag() const {
    return this->imaginary;
}

double Complex::abs() const {
    return sqrt(this->real * this->real + this->imaginary * this->imaginary);
}