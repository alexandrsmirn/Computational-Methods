#include "InterpolationalCalculator.h"

InterpolationalCalculator::InterpolationalCalculator(double begin, double end, int numPoints, std::function<double(double)> func)
        : begin(begin), end(end), func(func) {
   this->generateInterpolationTable(numPoints);
}

InterpolationalCalculator::Table InterpolationalCalculator::createSortedInterpolationTable(double argument, int degree) {
    Table sortedInterpolationTable = this->interpolationTable;

    std::sort(sortedInterpolationTable.begin(), sortedInterpolationTable.end(),
                [argument](std::pair<double, double> pair1, std::pair<double, double> pair2) {
                    return abs(pair1.first - argument) < abs(pair2.first - argument);
                } );

    sortedInterpolationTable.resize(degree);
    return sortedInterpolationTable;
}

void InterpolationalCalculator::generateInterpolationTable(int newNumber) {
    numPoints = newNumber;
    double step = (end - begin) / numPoints;
    interpolationTable.clear();

    for (int i = 0; i < numPoints - 1; i++) {
        double x = begin + i * step;
        interpolationTable.push_back(std::make_pair(x, func(x)));
    }
    interpolationTable.push_back(std::make_pair(end, func(end)));
}


void InterpolationalCalculator::printTable() {
    std::cout << "Point\t\t\t| Value\n";
    for (auto const& pair : interpolationTable) {
        std::cout << pair.first << "\t| " << pair.second << '\n';
    }
}