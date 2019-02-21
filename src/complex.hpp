//
// Created by Spark on 20/02/2019.
//

#ifndef CI_OPENGL_TEMPLATE_COMPLEX_HPP
#define CI_OPENGL_TEMPLATE_COMPLEX_HPP

#include <iostream>
#include <cmath>

/**
 * @file complex.hpp
 * @author Rok Kos <kosrok97@gmail.com>
 * @brief Class that represent complex number.
 */

 /*! A class to represent a Complex number */
class Complex {
private:
    double real; /*!< Real part of the complex */
    double imaginary; /*!< Imaginary part of the complex */

public:
    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
    Complex(double=0, double=0);

    //! A copy constructor
    /*!
      A more elaborate description of the copy constructor.
    */
    Complex(const Complex& rhs);

    //! A destructor.
    /*!
      A more elaborate description of the destructor.
    */
    ~Complex();

    Complex& operator=(const Complex& rhs); //!< Assigment operator

    double getReal() const; //!< Get the real part

    double getImag() const; //!< Get the imaginary part

    double abs() const; //!< Get the absolute (sqrt(R² + I²))
};

#endif //CI_OPENGL_TEMPLATE_COMPLEX_HPP
