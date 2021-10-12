#include <math.h>
#include <iostream>
#include "NumericalDifferentiator.h"

double func(double x) {
    return exp(1.5*x);
}

double funcFirstDeriv(double x) {
    return 1.5*func(x);
}

double funcSecondDeriv(double x) {
    return 2.25*func(x);
}

int main() {
    double begin;
    double stepLength;
    unsigned int stepCount;

    std::cout << "Enter begin point -> " << std::endl;
    std::cin >> begin;
    std::cout << "Enter length of a step -> ";
    std::cin >> stepLength;
    std::cout << "Enter count of steps -> ";
    std::cin >> stepCount;

    auto differentiator = NumericalDifferentiator(begin, stepLength, stepCount, func, funcFirstDeriv, funcSecondDeriv);

    std::cout << "\nArgument-value table:\n";
    differentiator.printTable(std::cout);
    std::cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";

    while (true) {
        std::cout << "Enter begin point -> " << std::endl;
        std::cin >> begin;
        std::cout << "Enter length of a step -> ";
        std::cin >> stepLength;
        std::cout << "Enter count of steps -> ";
        std::cin >> stepCount;
        std::cout << '\n';

        differentiator.setParams(begin, stepLength, stepCount);
        differentiator.printTable(std::cout);
        std::cout << "-----------------------------------------------------------------------------------------------------------------------------------\n";
    }
}