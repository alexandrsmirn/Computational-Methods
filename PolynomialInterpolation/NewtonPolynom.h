#pragma once

#include "PolynomCalculator.h"

class NewtonPolynom : public PolynomCalculator {
private:
    std::vector<std::vector<double>> dividedDiffTable;

    void createDividedDiffTable(Table const& sortedInterpolationTable);

public:
    NewtonPolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : PolynomCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override;
};