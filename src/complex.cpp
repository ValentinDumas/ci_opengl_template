#include "complex.hpp"

Complex::Complex(double _real, double _imaginary) {
    this->real = _real;
    this->imaginary = _imaginary;
}

Complex::Complex(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;
}

Complex::~Complex() {

}

Complex& Complex::operator=(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;

    return *this;
}

/*! @fn getReal()
   *   @brief Get the real part
   *   @return The complex's real part
   */
double Complex::getReal() const {
    return this->real;
}

double Complex::getImag() const {
    return this->imaginary;
}

double Complex::abs() const {
    return sqrt(this->real * this->real + this->imaginary * this->imaginary);
}