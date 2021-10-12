#pragma once

#include <vector>
#include <functional>
#include <iostream>

class InterpolationalCalculator {
protected:
    using Table = std::vector<std::pair<double, double>>;

    double begin;
    double end;
    int numPoints;
    std::vector<std::pair<double, double>> interpolationTable;
    std::function<double(double)> func;

    void  generateInterpolationTable(int newNumber);
    Table createSortedInterpolationTable(double argument, int degree) const;
    
    InterpolationalCalculator(double begin, double end, int numPoints, std::function<double(double)> func);
public:
    void printTable(std::ostream & output) const;
};
