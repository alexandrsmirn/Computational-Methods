#include <iostream>
#include <vector>
#include <math.h>
#include <functional>

#include "LagrangePolynom.h"
#include "NewtonPolynom.h"

double f(double x) {
    return cos(x) + 2 * x;
}

int main() {
    std::cout.precision(18);
    std::cout.setf(std::ios::fixed);

    double begin;
    double end;
    int numPoints;
    double argument;
    int degree;

    std::cout << "Enter begin and end" << std::endl;
    std::cin >> begin >> end;
    std::cout << "Enter number of points -> ";
    std::cin >> numPoints;

    auto lagrangeCalculator = LagrangePolynom(begin, end, numPoints, f);
    auto   newtonCalculator =   NewtonPolynom(begin, end, numPoints, f);

    std::cout << "\nInterpolation table:\n";
    lagrangeCalculator.printTable(std::cout);
    std::cout << "\n---------------------------------------------------------------\n";

    while (true) {
        std::cout << "Enter polynom degree -> ";
        std::cin >> degree;

        if (degree > numPoints) {
            std::cout << "Degree must not be greater than " << numPoints << '\n';
            std::cout << "---------------------------------------------------------------\n";
            continue;
        }

        std::cout << "Enter argument to calculate function -> ";
        std::cin >> argument;

        double exactValue = f(argument);
        double lagrangePolyniminalValue = lagrangeCalculator.getInterpolatedValue(argument, degree);
        double newtonPolyniminalValue   = newtonCalculator  .getInterpolatedValue(argument, degree);

        std::cout << "\nExact function value:                   " << exactValue << '\n';
        std::cout << "--------\n";
        std::cout << "Approximate Lagrange value:             " << lagrangePolyniminalValue << '\n';
        std::cout << "Lagrange error:                         " << abs(lagrangePolyniminalValue - exactValue) << '\n';
        std::cout << "--------\n";
        std::cout << "Approximate Newton value:               " << newtonPolyniminalValue << '\n';
        std::cout << "Newton error:                           " << abs(newtonPolyniminalValue - exactValue) << '\n';
        std::cout << "---------------------------------------------------------------\n";
    }
}
