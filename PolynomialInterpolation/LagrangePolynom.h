#pragma once

#include "InterpolationalCalculator.h"
#include "IPolynomCalculator.h"

class LagrangePolynom : public InterpolationalCalculator, public IPolynomCalculator {
private:  
    double calculateFundamentalPoly(double argument, int pointNumber, Table const& sortedInterpolationTable) const;

public:
    LagrangePolynom(double begin, double end, int numPoints, std::function<double(double)> func)
        : InterpolationalCalculator(begin, end, numPoints, func) {}

    double getInterpolatedValue(double argument, int degree) override;
};