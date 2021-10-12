#include <math.h>

#include "ReverseInterpolator.h"
#include "MonoReverseInterpolator.h"

double f(double x) {
    return cos(x) + 2 * x;
}

int main() {
    std::cout.precision(18);
    std::cout.setf(std::ios::fixed);

    double begin;
    double end;
    int numPoints;
    double value;
    int degree;
    int splitCount;
    double eps;

    std::cout << "Enter begin and end" << std::endl;
    std::cin >> begin >> end;
    std::cout << "Enter number of points -> ";
    std::cin >> numPoints;
    std::cout << "Enter split count and eps -> ";
    std::cin >> splitCount >> eps;

    auto revInterpolator = ReverseInterpolator(begin, end, numPoints, eps, splitCount, f);
    auto monRevInterpolator = MonotoneReverseInterpolator(begin, end, numPoints, f);

    std::cout << "\nInterpolation table:\n";
    revInterpolator.printTable(std::cout);
    std::cout << "\n---------------------------------------------------------------\n";

    while (true) {
        std::cout << "Enter polynom degree -> ";
        std::cin >> degree;

        if (degree > numPoints) {
            std::cout << "Degree must not be greater than " << numPoints << '\n';
            std::cout << "---------------------------------------------------------------\n";
            continue;
        }

        std::cout << "Enter function value to calculate arguments -> ";
        std::cin >> value;

        std::vector<double> revInterpResult = revInterpolator.getArguments(value, degree);
        std::vector<double> monRevInterpResult = monRevInterpolator.getArguments(value, degree);


        std::cout << "\nMonotone reverse interpolation result:\n";
        std::cout << "Value\t\t\t| Error\n";
        for (auto const& argument : monRevInterpResult) {
            std::cout << argument << "\t| " << abs(f(argument) - value) << '\n';
        }
        std::cout << "--------\n";
        std::cout << "Reverse interpolation results:\n";
        std::cout << "Value\t\t\t| Error\n";
        for (auto const& argument : revInterpResult) {
            std::cout << argument << "\t| " << abs(f(argument) - value) << '\n';
        }
        std::cout << "---------------------------------------------------------------\n";
    }
}