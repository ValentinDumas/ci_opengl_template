//
// Created by Spark on 20/02/2019.
//

#include <iostream>

#include "complex.hpp"

int main_tests(int argc, char **argv) {
    Complex a(3,5);
    Complex b(3,0);
    Complex c(a);

    std::cout << a.getReal() << " " << a.getImag() << " " << a.abs() << std::endl;
    std::cout << b.getReal() << " " << b.getImag() << " " << b.abs() << std::endl;
    std::cout << c.getReal() << " " << c.getImag() << " " << c.abs() << std::endl;

    return 0;
}