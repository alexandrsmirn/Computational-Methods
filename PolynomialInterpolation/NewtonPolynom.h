#pragma once

#include "InterpolationalCalculator.h"
#include "IPolynomCalculator.h"

class NewtonPolynom : public InterpolationalCalculator, public IPolynomCalculator {
private:
    using DiffTable = std::vector<std::vector<double>>;

    DiffTable createDividedDiffTable(Table const& sortedInterpolationTable) const;
public:
    NewtonPolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : InterpolationalCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) const override;
};
