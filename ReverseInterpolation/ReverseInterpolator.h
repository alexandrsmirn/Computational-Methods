#pragma once

#include "../PolynomialInterpolation/LagrangePolynom.h"
#include "IReverseInterpolator.h"


class ReverseInterpolator : public LagrangePolynom, public IReverseInterpolator {
private:
    double const eps;
    int const splitCount;

    double getInterpolatedValue(double argument, int degree) const override {
        return LagrangePolynom::getInterpolatedValue(argument, degree);
    };

public:
    ReverseInterpolator(double begin, double end, int numPoints, double eps, int splitCount, std::function<double(double)> func)
            : LagrangePolynom(begin, end, numPoints, func), eps(eps), splitCount(splitCount) {}

    std::vector<double> getArguments(double functionValue, int degree) const;
};