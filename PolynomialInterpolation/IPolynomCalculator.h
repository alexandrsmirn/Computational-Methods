#pragma once

class IPolynomCalculator {
public:
    virtual double getInterpolatedValue(double argument, int degree) const = 0;
    virtual ~IPolynomCalculator() {};
};
