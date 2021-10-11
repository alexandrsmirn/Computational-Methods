#pragma once

#include "PolynomCalculator.h"

class LagrangePolynom : public PolynomCalculator {
private:  
    double calculateFundamentalPoly(double argument, int pointNumber, Table const& sortedInterpolationTable);

public:
    LagrangePolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : PolynomCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override;
};