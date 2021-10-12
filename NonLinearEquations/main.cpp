#include "EquationSolver.h"
#include <math.h>
#include <iostream>

double function(double x) {
    return 1.2*pow(x, 4) + 2*pow(x, 3) - 13*pow(x, 2) - 14.2*x - 24.1;
}

double functionFirstDerivative(double x) {
    return 4.8*pow(x,3) + 6*pow(x, 2) - 26*x -14.2; 
}

int main() {
    int const A = -5;
    int const B =  5;
    double const eps = 1e-6;

    //std::cout.setf(std::ios::fixed);
    std::cout.precision(15);

    int splitCount;
    std::cout << "Enter split number\n-> ";
    std::cin >> splitCount;

    std::vector<Segment> separatedRoots = getSeparatedRoots(A, B, splitCount, function);

    std::cout << "Here is the list of the separated roots:\n";
    for (Segment const& segment : separatedRoots) {
        std::cout << "(" << segment.begin << ", " << segment.end << ")\n";
    }

    clarifyRoots(separatedRoots, AlgorithmMethod::newton, eps, function, functionFirstDerivative);

    return 0;
}