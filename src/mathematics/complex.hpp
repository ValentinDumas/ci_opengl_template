#ifndef CI_TEMPLATE_COMPLEX_HPP
#define CI_TEMPLATE_COMPLEX_HPP

#include <iostream>
#include <cmath>

/**
 * @file complex.hpp
 * @author Valentin Dumas <sp4rk76@gmail.com>
 * @brief Class that represent complex number.
 */

 /** @class Complex
  *  @brief A class to represent a Complex number.
  *  A more detailed class description
  */
class Complex {
private:
    /** @var double real
     *  @brief The real part of the complex number.
     */
    double real;

    /** @var double imaginary
     *  @brief The imaginary part of the complex number.
     */
    double imaginary;

public:
    /** @fn Complex(double=0, double=0)
     *  @brief Constructor
     */
    Complex(double=0, double=0);

    /** @fn Complex(const Complex& rhs)
     *  @brief Copy constructor
     *  @param rhs the object to copy
     */
    Complex(const Complex& rhs);

    /** @fn ~Complex()
     *  @brief Destructor
     */
    ~Complex();

    /** @fn Complex& operator=(const Complex& rhs)
     *  @param rhs
     *  @return the resultant operator after the assigment
     */
    Complex& operator=(const Complex& rhs);

    /** @fn double getReal() const
    *   @brief Get the real part
    *   @return The complex's imaginary part
    */
    double getReal() const;

    /** @fn double getImag() const
    *   @brief Get the imaginary part
    *   @return The complex's imaginary part
    */
    double getImag() const;

    /** @fn double abs() const
    *   @brief Get the absolute (sqrt(R² + I²))
    *   @return The complex's absolute
    */
    double abs() const;
};

#endif
