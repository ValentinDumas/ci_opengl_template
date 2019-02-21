#include "complex.hpp"

/**
 * @file complex.cpp
 * @author Valentin Dumas <sp4rk76@gmail.com>
 * @brief Class that represent complex number.
 */

/** @fn Complex::Complex(double _real, double _imaginary)
     *  @brief Constructor
     *  @param _real réel
     *  @param _imaginary imaginaire
     */
Complex::Complex(double _real, double _imaginary) {
    this->real = _real;
    this->imaginary = _imaginary;
}

/** @fn Complex::Complex(const Complex& rhs)
 *  @brief Copy constructor
 *  @param rhs the object to copy
 */
Complex::Complex(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;
}

/** @fn Complex::~Complex()
 *  @brief Destructor
 */

Complex::~Complex() {

}

/** @fn Complex& Complex::operator=(const Complex& rhs)
 *  @param rhs
 *  @return the resultant operator after the assigment
 */
Complex& Complex::operator=(const Complex& rhs) {
    this->real = rhs.real;
    this->imaginary = rhs.imaginary;

    return *this;
}

/** @fn Complex::getReal()
*   @brief Get the real part
*   @return The complex's real part
*/
double Complex::getReal() const {
    return this->real;
}

/** @fn Complex::getImaginary()
*   @brief Get the imaginary part
*   @return The complex's imaginary part
*/
double Complex::getImag() const {
    return this->imaginary;
}

/** @fn Complex::abs()
*   @brief Get the absolute (sqrt(R² + I²))
*   @return The complex's absolute
*/
double Complex::abs() const {
    return sqrt(this->real * this->real + this->imaginary * this->imaginary);
}