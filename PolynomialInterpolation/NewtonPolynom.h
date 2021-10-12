#pragma once

#include "InterpolationalCalculator.h"
#include "IPolynomCalculator.h"

class NewtonPolynom : public InterpolationalCalculator, public IPolynomCalculator {
private:
    std::vector<std::vector<double>> dividedDiffTable;

    void createDividedDiffTable(Table const& sortedInterpolationTable);

public:
    NewtonPolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : InterpolationalCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override;
};