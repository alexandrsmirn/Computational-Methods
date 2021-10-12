#pragma once

#include "../PolynomialInterpolation/NewtonPolynom.h"
#include "IReverseInterpolator.h"

class MonotoneReverseInterpolator : public NewtonPolynom, public IReverseInterpolator {
private:
    void invertTable();
    double getInterpolatedValue(double argument, int degree) const override { return NewtonPolynom::getInterpolatedValue(argument, degree); };
public:
    MonotoneReverseInterpolator(double begin, double end, int numPoints, std::function<double(double)> func)
            : NewtonPolynom(begin, end, numPoints, func) {
        invertTable();
    };

    std::vector<double> getArguments(double functionValue, int degree) const;
};